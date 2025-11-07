#include "Sprocket.h"
#include "Json.h"

#include <SPETS/Util.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <unordered_map>

#include <filesystem>
#include <locale>
#include <codecvt>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::filesystem::path Sprocket::getStreamingAssetsPath()
{
	std::filesystem::path programFiles = SPETS::getFolderPath( FOLDERID_ProgramFilesX86 );
	return programFiles / "Steam" / "steamapps" / "common" / "Sprocket" / "Sprocket_Data" / "StreamingAssets";
}

std::filesystem::path Sprocket::getSprocketDataPath()
{
	std::filesystem::path path = SPETS::getFolderPath( FOLDERID_Documents );
	return path / "My Games" / "Sprocket";
}

std::filesystem::path Sprocket::getFactionPath( const std::string& _name )
{
	std::filesystem::path data = Sprocket::getSprocketDataPath();
	return data / "Factions" / _name;
}

std::filesystem::path Sprocket::getBlueprintPath( const std::string& _faction, const std::string& _name )
{
	if ( !Sprocket::doesFactionExist( _faction ) )
		return "";

	return Sprocket::getFactionPath( _faction ) / "Blueprints" / "Vehicles" / ( _name + ".blueprint" );
}

std::filesystem::path Sprocket::getPlateStructurePath( const std::string& _faction, const std::string& _name )
{
	if ( !Sprocket::doesFactionExist( _faction ) )
		return "";

	return Sprocket::getFactionPath( _faction ) / "Blueprints" / "Plate Structures" / ( _name + ".blueprint" );
}

bool Sprocket::doesFactionExist( const std::string& _name )
{
	return std::filesystem::is_directory( getFactionPath( _name ) );
}

bool Sprocket::doesBlueprintExist( const std::string& _faction, const std::string& _name )
{
	std::filesystem::path filePath = getBlueprintPath( _faction, _name );
	return std::filesystem::exists( filePath );
}

bool Sprocket::createCompartmentFromMesh( const std::string& _path, MeshData& _outMesh )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( _path, aiProcess_JoinIdenticalVertices );

	if ( scene == nullptr || scene->mNumMeshes == 0 )
		return false;

	std::unordered_map< uint16_t, std::vector<uint16_t> > edgeMap{};
	std::unordered_map< uint32_t, uint32_t > indexRemap{};

	uint32_t indexOffset = 0; // global mesh vertex offset
	uint32_t indexShift = 0; // so we can properly remove duplicate vertices and shift indices down

	MeshData meshData{ };
	meshData.name = scene->mName.C_Str();

	for ( size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++ )
	{
		aiMesh* mesh = scene->mMeshes[ meshIndex ];

		// setup vertices
		for ( size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++ )
		{
			aiVector3D vert = mesh->mVertices[ vertexIndex ];
			int duplicateIndex = -1;

			for ( size_t checkIndex = 0; checkIndex < vertexIndex; checkIndex++ )
			{
				if ( checkIndex == vertexIndex )
					continue;

				aiVector3D checkVert = mesh->mVertices[ checkIndex ];
				if ( ( checkVert - vert ).Length() > 0.001 )
					continue;

				duplicateIndex = checkIndex;
				break;
			}

			if ( duplicateIndex == -1 )
			{
				meshData.mesh.vertexPositions.push_back( vert.x );
				meshData.mesh.vertexPositions.push_back( vert.y );
				meshData.mesh.vertexPositions.push_back( vert.z );

				// shift remap
				if ( indexShift > 0 )
					indexRemap[ vertexIndex + indexOffset ] = vertexIndex + indexOffset - indexShift;
			}
			else
			{
				uint32_t remapIndex = duplicateIndex + indexOffset;

				// check if remapping to a shifted index
				if ( indexRemap.contains( remapIndex ) )
					remapIndex = indexRemap[ remapIndex ];

				indexRemap[ vertexIndex + indexOffset ] = remapIndex;

				indexShift++;
			}
		}

		for ( size_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++ )
		{
			aiFace face = mesh->mFaces[ faceIndex ];
			if ( face.mNumIndices != 3 && face.mNumIndices != 4 )
				continue;

			Sprocket::SerializedFace serializedFace{};
			for ( size_t i = 0; i < face.mNumIndices; i++ )
			{
				uint16_t edgeA = indexOffset + face.mIndices[ i ];
				uint16_t edgeB = indexOffset + face.mIndices[ ( i + 1 ) % face.mNumIndices ];

				if ( indexRemap.contains( edgeA ) ) edgeA = indexRemap[ edgeA ];
				if ( indexRemap.contains( edgeB ) ) edgeB = indexRemap[ edgeB ];

				serializedFace.vertices.push_back( edgeA );
				serializedFace.thicknesses.push_back( 1.0f );

				if ( edgeMap.count( edgeB ) == 0 )
					edgeMap[ edgeA ].push_back( edgeB );
			}
			meshData.mesh.serializedFaces.push_back( serializedFace );
		}

		//printf( "Parsed %s vertices\n", mesh->mName.C_Str() );
		indexOffset += mesh->mNumVertices;
	}

	for ( auto e : edgeMap )
	{
		for ( size_t i = 0; i < e.second.size(); i++ )
		{
			meshData.mesh.serializedEdges.push_back( e.second[ i ] );
			meshData.mesh.serializedEdges.push_back( e.first );
			meshData.mesh.serializedEdgeFlags.push_back( SerializedEdgeFlags_None );
		}
	}

	//printf( "Constructed edge map\n" );

	_outMesh = meshData;
	return true;
}

bool Sprocket::loadBlueprint( const std::string& _faction, const std::string& _name, VehicleBlueprint& _out )
{
	std::filesystem::path path = getBlueprintPath( _faction, _name );
	return loadBlueprintFromFile( path, _out );
}

bool Sprocket::loadBlueprintFromFile( const std::filesystem::path& _path, VehicleBlueprint& _out )
{
	std::ifstream f{ _path };
	if ( !f )
		return false; // failed to open blueprint file 

	nlohmann::json json = nlohmann::json::parse( f );

	try
	{
		_out = json.get<Sprocket::VehicleBlueprint>();
		return true;
	}
	catch ( ... )
	{
		_out = {};
		return false; // JSON parsing failure
	}
}

bool Sprocket::loadBlueprintFromFile( const std::string& _path, MeshData& _out )
{
	std::ifstream f( _path );
	if ( !f )
		return false;

	nlohmann::json json = nlohmann::json::parse( f );

	if ( json[ "v" ] == "2.0" )
	{
		printf( "Vehicle Blueprint, NOT IMPLEMENTED YET" );
		return false;
	}

	_out = json.get<Sprocket::MeshData>();

	return true;
}

bool Sprocket::saveCompartmentToFile( const MeshData& _compartment, const std::string& _path )
{
	std::ofstream f( _path );
	if ( !f )
		return false;

	nlohmann::json json = _compartment;
	f << json.dump();

	return true;
}

bool Sprocket::saveCompartmentToFaction( const MeshData& _compartment, const std::string& _faction, const std::string& _name )
{
	std::filesystem::path path = Sprocket::getPlateStructurePath( _faction, _name );
	Sprocket::saveCompartmentToFile( _compartment, path.string() );

	return false;
}

bool Sprocket::exportBlueprintToFile( const VehicleBlueprint& _blueprint )
{
	int unnamedMeshes = 0;
	//printf( "Exporting %s ... ", _blueprint->header.name.c_str() );
	if ( !std::filesystem::create_directory( _blueprint.header.name ) )
		return false;

	for ( size_t m = 0; m < _blueprint.meshes.size(); m++ )
	{
		std::string filename = "";

		const Sprocket::MeshData& mesh = _blueprint.meshes[ m ].meshData;
		if ( mesh.name == "" )
			filename = std::format( "unnamed{}", unnamedMeshes++ );
		else
			filename = mesh.name;

		std::filesystem::path path = _blueprint.header.name + "/" + filename;
		exportBlueprintToFile( mesh, path );
	}

	//printf( "Done\n" );

	return true;
}

bool Sprocket::exportBlueprintToFile( const MeshData& _mesh, std::filesystem::path _path )
{
	std::ofstream f( _path.replace_extension( ".obj" ) );
	if ( !f )
		return false;

	f << "# SPETS " << SPETS::VERSION_STR << "\n";

	if ( _mesh.name == "" )
		f << "o PlateStructure\n";
	else
		f << std::format( "o {}\n", _mesh.name );

	float x = 0.0f, y = 0.0f, z = 0.0f;
	for ( size_t v = 0; v < _mesh.mesh.getNumVertices(); v++ )
	{
		_mesh.mesh.getVertexPosition( v, &x, &y, &z );
		f << std::format( "v {} {} {}\n", x, y, z );
	}

	for ( size_t i = 0; i < _mesh.mesh.serializedFaces.size(); i++ )
	{
		const Sprocket::SerializedFace& face = _mesh.mesh.serializedFaces[ i ];
		f << "f ";
		for ( size_t v = 0; v < face.vertices.size(); v++ )
			f << ( face.vertices[ v ] + 1 ) << " ";
		f << "\n";
	}

	return true;
}

std::string Sprocket::getCurrentFaction()
{
	std::filesystem::path appdata = SPETS::getFolderPath( FOLDERID_LocalAppDataLow );
	std::filesystem::path path = appdata / "HD" / "Sprocket" / "CurrentFaction";

	std::ifstream f{ path };
	if ( !f )
		return "Default"; // failed to open CurrentFaction file 

	std::stringstream s{};
	s << f.rdbuf();
	return s.str();
}

Sprocket::FactionInfo Sprocket::getFactionInfo( const std::string& _name )
{
	std::filesystem::path path = Sprocket::getFactionPath( _name );
	std::ifstream f( path / ( _name + ".fdef") );
	if ( !f )
		return {};

	nlohmann::json json = nlohmann::json::parse( f );

	FactionInfo info{};
	json.at( "name" ).get_to( info.name );
	json.at( "designPrefix" ).get_to( info.designPrefix );
	json.at( "designCounter" ).get_to( info.designCounter );

	return info;
}

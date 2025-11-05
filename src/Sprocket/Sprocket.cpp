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

bool Sprocket::loadCompartmentFromFile( const std::string& _path, MeshData& _out )
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

bool Sprocket::saveCompartmentToFile( const std::string& _path, const MeshData& _compartment )
{
	std::ofstream f( _path );
	if ( !f )
		return false;

	nlohmann::json json = _compartment;
	f << json.dump();
	
    return true;
}

bool Sprocket::importMesh( const std::string& _path, MeshData& _outMesh )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( _path, aiProcess_JoinIdenticalVertices  );

	if ( scene == nullptr || scene->mNumMeshes == 0 )
		return false;
	
	std::unordered_map< uint16_t, uint16_t > edgeMap{};
	uint32_t indexOffset = 0;
	MeshData meshData{ };
	meshData.name = scene->mName.C_Str();

	for ( size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++ )
	{
		aiMesh* mesh = scene->mMeshes[ meshIndex ];
		
		// setup vertices
		for ( size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++ )
		{
			aiVector3D vert = mesh->mVertices[ vertexIndex ];
			meshData.mesh.vertexPositions.push_back( vert.x );
			meshData.mesh.vertexPositions.push_back( vert.y );
			meshData.mesh.vertexPositions.push_back( vert.z );
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
				uint16_t edgeB = indexOffset + face.mIndices[ (i + 1) % face.mNumIndices ];

				serializedFace.vertices.push_back( edgeA );
				serializedFace.thicknesses.push_back( 1.0f );

				if ( edgeMap.count( edgeA ) == 0 )
					edgeMap[ edgeA ] = edgeB;
			}
			meshData.mesh.serializedFaces.push_back( serializedFace );
		}

		//printf( "Parsed %s vertices\n", mesh->mName.C_Str() );
		indexOffset += mesh->mNumVertices;
	}

	for ( auto e : edgeMap )
	{
		meshData.mesh.serializedEdges.push_back( e.first );
		meshData.mesh.serializedEdges.push_back( e.second );
		meshData.mesh.serializedEdgeFlags.push_back( SerializedEdgeFlags_None );
		
		meshData.mesh.serializedEdges.push_back( e.second );
		meshData.mesh.serializedEdges.push_back( e.first );
		meshData.mesh.serializedEdgeFlags.push_back( SerializedEdgeFlags_None );
	}

	//printf( "Constructed edge map\n" );

	_outMesh = meshData;
	return true;
}

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

bool Sprocket::doesFactionExist( const std::string& _name )
{
	return std::filesystem::is_directory( getFactionPath( _name ) );
}

bool Sprocket::doesBlueprintExist( const std::string& _faction, const std::string& _name )
{
	std::filesystem::path filePath = getBlueprintPath( _faction, _name );
	return std::filesystem::exists( filePath );
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

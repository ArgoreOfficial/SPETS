#include "Sprocket.h"
#include "Json.h"

#include <SPETS/Util.h>
#include <Sprocket/Error.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <unordered_map>

#include <filesystem>
#include <locale>
#include <codecvt>

#include <Sprocket/IntermediateMesh.h>

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
	{
		SPROCKET_PUSH_ERROR( "Faction '{}' does not exist", _name );
		return "";
	}

	return Sprocket::getFactionPath( _faction ) / "Blueprints" / "Plate Structures" / ( _name + ".blueprint" );
}

Sprocket::BlueprintType Sprocket::getBlueprintFileType( const std::filesystem::path& _path )
{
	std::ifstream f{ _path };
	if ( !f )
		return BlueprintType_None; // failed to open blueprint file 

	nlohmann::json json = nlohmann::json::parse( f );
	if ( json.contains( "rivets" ) )
		return BlueprintType_Compartment; // only compartments have rivets, for now

	if ( json.contains( "blueprints" ) ) 
		return BlueprintType_Vehicle; // only vehicles have blueprints, for now

	return BlueprintType_None; // faulty blueprint file
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

bool Sprocket::createCompartmentFromMesh( const std::string& _path, MeshData& _outMesh, ImportMeshFlags _flags )
{
	Sprocket::IntermediateMesh immesh;
	
	if ( !Sprocket::createIntermediateMeshFromFile( _path, immesh ) )
		return false;

	immesh.mergeDuplicateVertices();

	int flips = 0;
	if ( _flags & ImportMeshFlags_FlipX ) { immesh.flipX(); flips++; }
	if ( _flags & ImportMeshFlags_FlipY ) { immesh.flipY(); flips++; }
	if ( _flags & ImportMeshFlags_FlipZ ) { immesh.flipZ(); flips++; }

	if ( flips == 1 || flips == 3 )
		immesh.reverseWindingOrder();

	return immesh.createCompartment( _outMesh );
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
		SPROCKET_PUSH_ERROR( "Loaded vehicle blueprint file. Currently unsupported." );
		return false;
	}

	_out = json.get<Sprocket::MeshData>();

	return true;
}

bool Sprocket::saveBlueprintToFile( const VehicleBlueprint& _blueprint, const std::string& _path )
{
	std::ofstream f( _path );
	if ( !f )
	{
		SPROCKET_PUSH_ERROR( "Failed to open file {}", _path );
		return false;
	}

	nlohmann::json json = _blueprint;
	f << json.dump();

	return true;
}

bool Sprocket::saveBlueprintToFaction( const VehicleBlueprint& _blueprint, const std::string& _faction, const std::string& _name )
{
	std::filesystem::path path = Sprocket::getBlueprintPath( _faction, _name );
	return Sprocket::saveBlueprintToFile( _blueprint, path.string() );
}

bool Sprocket::saveCompartmentToFile( const MeshData& _compartment, const std::string& _path )
{
	std::ofstream f( _path );
	if ( !f )
	{
		SPROCKET_PUSH_ERROR( "Failed to open file {}", _path );
		return false;
	}

	nlohmann::json json = _compartment;
	f << json.dump();

	return true;
}

bool Sprocket::saveCompartmentToFaction( const MeshData& _compartment, const std::string& _faction, const std::string& _name )
{
	std::filesystem::path path = Sprocket::getPlateStructurePath( _faction, _name );
	return Sprocket::saveCompartmentToFile( _compartment, path.string() );
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
	{
		SPROCKET_PUSH_ERROR( "Failed to open CurrentFaction" );
		return "Default"; // failed to open CurrentFaction file 
	}

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

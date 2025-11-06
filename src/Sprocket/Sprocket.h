#pragma once

#include <Sprocket/PlateMesh/PlateMesh.h>
#include <Sprocket/CustomBattle.h>

#include <string>
#include <filesystem>
#include <vector>

namespace Sprocket {

struct VehicleObjectBlueprint
{
	// TODO
};

struct SerializableBlueprint
{
	// TODO
};

struct VehicleBlueprintHeader
{
	std::string version;
	std::string name;
	std::string gameVersion;
	int mass;
	std::string creationDate;
	std::string classification;
	std::string description;
};

struct VehicleBlueprint
{
	std::string version;
	VehicleBlueprintHeader header;
	std::vector<SerializableBlueprint> blueprints;
	std::vector<SerializableMesh> meshes;
};

struct FactionInfo
{
	std::string name = "";
	std::string designPrefix = "";
	int designCounter = 0;
};

bool loadCompartmentFromFile( const std::string& _path, MeshData& _out );
bool saveCompartmentToFile( const MeshData& _compartment, const std::string& _path );
bool saveCompartmentToFaction( const MeshData& _compartment, const std::string& _faction, const std::string& _name );

bool createCompartmentFromMesh( const std::string& _path, MeshData& _outMesh );

std::filesystem::path getStreamingAssetsPath();
std::filesystem::path getSprocketDataPath();
std::filesystem::path getFactionPath( const std::string& _name );
std::filesystem::path getBlueprintPath( const std::string& _faction, const std::string& _name );
std::filesystem::path getPlateStructurePath( const std::string& _faction, const std::string& _name );

bool doesFactionExist( const std::string& _name );
bool doesBlueprintExist( const std::string& _faction, const std::string& _name );
VehicleBlueprint* loadBlueprint( const std::string& _faction, const std::string& _name );
bool exportBlueprintToFile( VehicleBlueprint* _blueprint );

std::string getCurrentFaction();
FactionInfo getFactionInfo( const std::string& _name );

}
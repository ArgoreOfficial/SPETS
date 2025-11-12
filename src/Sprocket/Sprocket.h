#pragma once

#include <Sprocket/PlateMesh/PlateMesh.h>
#include <Sprocket/CustomBattle.h>
#include <Sprocket/VehicleBlueprint.h>

#include <string>
#include <filesystem>
#include <vector>

namespace Sprocket {

struct FactionInfo
{
	std::string name = "";
	std::string designPrefix = "";
	int designCounter = 0;
};

std::filesystem::path getStreamingAssetsPath();
std::filesystem::path getSprocketDataPath();
std::filesystem::path getFactionPath( const std::string& _name );
std::filesystem::path getBlueprintPath( const std::string& _faction, const std::string& _name );
std::filesystem::path getPlateStructurePath( const std::string& _faction, const std::string& _name );

bool quickImport( const std::filesystem::path& _path );

bool doesFactionExist( const std::string& _name );
bool doesBlueprintExist( const std::string& _faction, const std::string& _name );

bool createCompartmentFromMesh( const std::string& _path, MeshData& _outMesh );

bool loadBlueprint( const std::string& _faction, const std::string& _name, VehicleBlueprint& _out );
bool loadBlueprintFromFile( const std::filesystem::path& _path, VehicleBlueprint& _out );
bool loadBlueprintFromFile( const std::string& _path, MeshData& _out );

bool saveBlueprintToFile( const VehicleBlueprint& _blueprint, const std::string& _path );
bool saveBlueprintToFaction( const VehicleBlueprint& _blueprint, const std::string& _faction, const std::string& _name );

bool saveCompartmentToFile( const MeshData& _compartment, const std::string& _path );
bool saveCompartmentToFaction( const MeshData& _compartment, const std::string& _faction, const std::string& _name );

bool exportBlueprintToFile( const VehicleBlueprint& _blueprint );
bool exportBlueprintToFile( const MeshData& _mesh, std::filesystem::path _path );

std::string getCurrentFaction();
FactionInfo getFactionInfo( const std::string& _name );

}
#pragma once

#include <Sprocket/PlateMesh/PlateMesh.h>
#include <Sprocket/Blueprints/Blueprint.h>

#include <vector>
#include <string>

namespace Sprocket {

struct VehicleObjectBlueprint
{
	// TODO
};

struct SerializableBlueprint
{
	int id = 0;
	std::string type = "";
	Sprocket::Blueprint* blueprint = nullptr;
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
	std::vector<VehicleObjectBlueprint> objects;
	std::vector<SerializableMesh> meshes;
};

}
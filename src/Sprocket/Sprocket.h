#pragma once

#include "Sprocket/PlateMesh/PlateMesh.h"

#include <string>
#include <filesystem>

namespace Sprocket {

struct FactionInfo
{
	std::string name = "";
	std::string designPrefix = "";
	int designCounter = 0;
};

bool loadCompartmentFromFile( const std::string& _path, MeshData& _out );
bool saveCompartmentToFile( const std::string& _path, const MeshData& _compartment );
bool importMesh( const std::string& _path, MeshData& _outMesh );

std::filesystem::path getSprocketDataPath();
std::filesystem::path getFactionPath( const std::string& _name );

bool doesFactionExist( const std::string& _name );
std::string getCurrentFaction();
FactionInfo getFactionInfo( const std::string& _name );


}
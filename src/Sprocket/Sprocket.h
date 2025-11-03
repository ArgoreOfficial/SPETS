#pragma once

#include "Sprocket/PlateMesh/PlateMesh.h"


namespace Sprocket {

bool loadCompartmentFromFile( const std::string& _path, MeshData& _out );
bool saveCompartmentToFile( const std::string& _path, const MeshData& _compartment );
bool importMesh( const std::string& _path, MeshData& _outMesh );

bool doesFactionExist( const std::string& _name );
std::string getFactionPath( const std::string& _name );

}
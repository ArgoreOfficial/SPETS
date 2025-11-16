#pragma once

#include <Sprocket/VehicleBlueprint.h>

#include <vector>
#include <filesystem>

namespace Sprocket {

struct IntermediateVertex
{
	// change to wv::Vector3<Ty>?

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f; 
};

struct IntermediateFace
{
	std::vector<uint16_t> vertices;
};

struct IntermediateMesh
{
	std::vector<IntermediateVertex> vertices;
	std::vector<IntermediateFace> faces;

	bool appendIntermediateMesh( const IntermediateMesh& _mesh );
};

bool createIntermediateMeshFromFile( const std::filesystem::path& _path, IntermediateMesh& _out );

}
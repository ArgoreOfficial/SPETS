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

	IntermediateVertex operator+( const IntermediateVertex& _other )
	{
		return {
			x + _other.x,
			y + _other.y,
			z + _other.z
		};
	}
	
	IntermediateVertex operator-( const IntermediateVertex& _other )
	{
		return {
			x - _other.x,
			y - _other.y,
			z - _other.z
		};
	}

	float length() const { return std::sqrt( x * x + y * y + z * z ); }
};

struct IntermediateFace
{
	std::vector<uint16_t> vertices;
};

struct IntermediateMesh
{
	std::string name;
	std::vector<IntermediateVertex> vertices;
	std::vector<IntermediateFace> faces;

	void appendIntermediateMesh( const IntermediateMesh& _mesh );
	void mergeDuplicateVertices();

	void flipX() {
		for ( size_t i = 0; i < vertices.size(); i++ )
			vertices[ i ].x *= -1;
	}

	void flipY() {
		for ( size_t i = 0; i < vertices.size(); i++ )
			vertices[ i ].y *= -1;
	}

	void flipZ() {
		for ( size_t i = 0; i < vertices.size(); i++ )
			vertices[ i ].z *= -1;
	}

	void reverseWindingOrder();

	bool createCompartment( MeshData& _out );

};

bool createIntermediateMeshFromFile( const std::filesystem::path& _path, IntermediateMesh& _out );

}
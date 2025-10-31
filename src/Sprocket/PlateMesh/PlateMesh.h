#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "Rivets.h"

namespace Sprocket {

enum ThickenMode : uint8_t
{
	ThickenMode_AlongFaceNormal = 0,
	ThickenMode_Auto = 1,
	ThickenMode_AlongEdgeAuto = 2,
	ThickenMode_AlongEdgeManual = 4,
	ThickenMode_AlongVertexNormal = 8,
	ThickenMode_Horizontal = 16,
	ThickenMode_Sideways = 32,
	ThickenMode_Vertical = 64,
	ThickenMode_Lengthways = 128
};

struct SerializedFace
{
	std::vector<int32_t>  vertices;    // "v"
	std::vector<uint16_t> thicknesses; // "t"

	/*

	> tm is thicken mode, te is the index of the edge to thicken along
	> 4 int16s in one int64
	- Hamish 2025
	https://discord.com/channels/788349365466038283/788349366091513888/1433855222895214602

	*/

	union ThickenModes_t
	{
		ThickenMode arr[ 4 ];
		int32_t u32 = 16843009; // auto auto auto auto
	} thickenModes;  // "tm"

	union ThickenEdgeIndicies_t
	{
		uint16_t arr[ 4 ];
		uint64_t u64;
	} thickenEdgeIndicies; // "te"
};

enum SerializedEdgeFlags : uint8_t
{
	SerializedEdgeFlags_Sharp = 1
};

struct MeshBlueprint
{
	uint32_t majorVersion = 0;
	uint32_t minorVersion = 3;
	std::vector<float> vertexPositions;   // "vertices"
	std::vector<int32_t> serializedEdges; // "edges"
	std::vector<SerializedEdgeFlags> serializedEdgeFlags; // "edgeFlags"
	std::vector<SerializedFace> serializedFaces; // "faces"

	size_t getNumVertices() const { 
		return vertexPositions.size() / 3; 
	}

	void setVertexPosition( size_t _index, float _x, float _y, float _z ) {
		if ( _index < 0 || _index >= getNumVertices() )
			throw std::out_of_range( "Vertex index out of range" );

		size_t realIndex = _index * 3;
		vertexPositions[ realIndex + 0 ] = _x;
		vertexPositions[ realIndex + 1 ] = _y;
		vertexPositions[ realIndex + 2 ] = _z;
	}

	void getVertexPosition( size_t _index, float* _outX, float* _outY, float* _outZ ) {
		if ( _index < 0 || _index >= getNumVertices() )
			throw std::out_of_range( "Vertex index out of range" );

		size_t realIndex = _index * 3;
		if ( _outX ) *_outX = vertexPositions[ realIndex + 0 ];
		if ( _outY ) *_outY = vertexPositions[ realIndex + 1 ];
		if ( _outZ ) *_outZ = vertexPositions[ realIndex + 2 ];
	}

	void moveVertexPosition( size_t _index, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f ) {
		if ( _index < 0 || _index >= getNumVertices() )
			throw std::out_of_range( "Vertex index out of range" );

		size_t realIndex = _index * 3;
		vertexPositions[ realIndex + 0 ] += _x;
		vertexPositions[ realIndex + 1 ] += _y;
		vertexPositions[ realIndex + 2 ] += _z;
	}
};

/**
 * @brief Individual compartment mesh data. Can be saved as a Plate Structure .blueprint, or as part of a Blueprint mesh
 */
struct MeshData
{
	std::string version = "0.2"; 
	std::string name = "";
	uint32_t    smoothAngle = 0;
	uint32_t    gridSize = 1;
	std::string format = "freeform";

	MeshBlueprint mesh;
	Rivets rivets;
};

struct PlateStructureMesh
{
	uint32_t vuid;
	std::string type = "plateStructureMesh";
	MeshData meshData;
};

}


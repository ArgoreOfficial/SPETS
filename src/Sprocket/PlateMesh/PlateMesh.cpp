#include "PlateMesh.h"

void Sprocket::MeshBlueprint::setVertexPosition( size_t _index, float _x, float _y, float _z )
{
	if ( _index < 0 || _index >= getNumVertices() )
		throw std::out_of_range( "Vertex index out of range" );

	size_t realIndex = _index * 3;
	vertexPositions[ realIndex + 0 ] = _x;
	vertexPositions[ realIndex + 1 ] = _y;
	vertexPositions[ realIndex + 2 ] = _z;
}

void Sprocket::MeshBlueprint::getVertexPosition( size_t _index, float* _outX, float* _outY, float* _outZ )
{
	if ( _index < 0 || _index >= getNumVertices() )
		throw std::out_of_range( "Vertex index out of range" );

	size_t realIndex = _index * 3;
	if ( _outX ) *_outX = vertexPositions[ realIndex + 0 ];
	if ( _outY ) *_outY = vertexPositions[ realIndex + 1 ];
	if ( _outZ ) *_outZ = vertexPositions[ realIndex + 2 ];
}

void Sprocket::MeshBlueprint::moveVertexPosition( size_t _index, float _x, float _y, float _z )
{
	if ( _index < 0 || _index >= getNumVertices() )
		throw std::out_of_range( "Vertex index out of range" );

	size_t realIndex = _index * 3;
	vertexPositions[ realIndex + 0 ] += _x;
	vertexPositions[ realIndex + 1 ] += _y;
	vertexPositions[ realIndex + 2 ] += _z;
}

void Sprocket::MeshBlueprint::scaleVertexPosition( size_t _index, float _x, float _y, float _z )
{
	if ( _index < 0 || _index >= getNumVertices() )
		throw std::out_of_range( "Vertex index out of range" );

	size_t realIndex = _index * 3;
	vertexPositions[ realIndex + 0 ] *= _x;
	vertexPositions[ realIndex + 1 ] *= _y;
	vertexPositions[ realIndex + 2 ] *= _z;
}

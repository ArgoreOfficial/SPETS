#include "PlateMesh.h"

void Sprocket::MeshBlueprint::addFace( const std::vector<float>& _vertexPositions )
{
	SerializedFace face;

	for ( size_t i = 0; i < _vertexPositions.size(); i += 3 )
	{
		face.vertices.push_back( getNumVertices() );
		face.thicknesses.push_back( 1.0f );
		
		vertexPositions.push_back( _vertexPositions[ i ] );
		vertexPositions.push_back( _vertexPositions[ i + 1 ] );
		vertexPositions.push_back( _vertexPositions[ i + 2 ] );
	}

	face.thickenEdgeIndicies.u64 = 0;
	
	serializedFaces.push_back( face );
}

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

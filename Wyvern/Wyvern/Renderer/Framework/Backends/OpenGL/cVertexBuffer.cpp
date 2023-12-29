#include "Wyvern/Renderer/Framework/cVertexBuffer.h"

#include <glad/gl.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cVertexBuffer::cVertexBuffer( void )
{

}

///////////////////////////////////////////////////////////////////////////////////////

cVertexBuffer::~cVertexBuffer( void )
{

	glDeleteBuffers( 1, &m_handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexBuffer::create( void )
{

	glGenBuffers( 1, &m_handle );
	bind();

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexBuffer::bind( void )
{

	glBindBuffer( GL_ARRAY_BUFFER, m_handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexBuffer::bufferData( float* _data, unsigned long long _size )
{

	glBufferData( GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW );
	
}

#include "Wyvern/Renderer/Framework/cIndexBuffer.h"

#include <glad/gl.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cIndexBuffer::cIndexBuffer( void )
{

}

cIndexBuffer::~cIndexBuffer( void )
{
	glDeleteBuffers( 1, &m_handle );
}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cIndexBuffer::create( void )
{

	glGenBuffers( 1, &m_handle );
	bind();

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cIndexBuffer::bind( void )
{

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cIndexBuffer::bufferData( unsigned int* _data, unsigned long long _size )
{

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW );

}

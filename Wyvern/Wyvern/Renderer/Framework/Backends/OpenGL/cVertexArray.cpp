#include "Wyvern/Renderer/Framework/cVertexArray.h"

#include <glad/gl.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cVertexArray::cVertexArray( void )
{

}

///////////////////////////////////////////////////////////////////////////////////////

cVertexArray::~cVertexArray( void )
{

	glDeleteVertexArrays( 1, &m_handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexArray::create( void )
{

	glGenVertexArrays( 1, &m_handle );
	bind();

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexArray::bind( void )
{
	
	glBindVertexArray( m_handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cVertexArray::addLayout( cVertexBufferLayout _layout )
{

	const auto& elements = _layout.getElements();
	unsigned int offset  = 0;

	for ( unsigned int i = 0; i < elements.size(); i++ )
	{

		const auto& element = elements[ i ];

		glEnableVertexAttribArray( i );

		GLenum type = GL_UNSIGNED_BYTE;

		switch ( element.type )
		{
		case WV_TYPE::WV_FLOAT:
			type = GL_FLOAT;
			break;
		case WV_TYPE::WV_UINT:
			type = GL_UNSIGNED_INT;
			break;
		case WV_TYPE::WV_BYTE:
			type = GL_UNSIGNED_BYTE;
			break;
		}

		// normalized is always false here, though it can be easily changed
		glVertexAttribPointer( i, element.count, type, false, _layout.getStride(), (const void*)offset );
		offset += element.count * element.size;

	}

}

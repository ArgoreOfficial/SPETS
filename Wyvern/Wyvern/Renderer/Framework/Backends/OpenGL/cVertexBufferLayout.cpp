#include "Wyvern/Renderer/Framework/cVertexBufferLayout.h"

#include <glad/gl.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cVertexBufferLayout::cVertexBufferLayout( void )
{
}

///////////////////////////////////////////////////////////////////////////////////////

cVertexBufferLayout::~cVertexBufferLayout( void )
{
}

///////////////////////////////////////////////////////////////////////////////////////

void cVertexBufferLayout::push( WV_TYPE _type, unsigned int _count )
{

	unsigned int size = 0;

	switch ( _type )
	{
	case WV_TYPE::WV_FLOAT: 
		size = 4; 
		break;
	case WV_TYPE::WV_UINT: 
		size = 4; 
		break;
	case WV_TYPE::WV_BYTE: 
		size = 1; 
		break;
	}

	m_elements.push_back( { _type, _count, size } );
	m_stride += size * _count;

}

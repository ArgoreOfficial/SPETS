#include "cMaterial.h"
#include <Wyvern/Managers/cResourceManager.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cMaterial::cMaterial()
{

}

///////////////////////////////////////////////////////////////////////////////////////

cMaterial::~cMaterial()
{

	if ( m_texture )
	{

		cResourceManager::getInstance().unloadTexture( m_textureHandle );
		m_texture = nullptr;

	}

}

///////////////////////////////////////////////////////////////////////////////////////

void cMaterial::loadTexture( std::string _path )
{

	m_hasTexture = true;
	m_texturePath = _path;
	
	m_textureHandle = cResourceManager::getInstance().loadTexture( m_texturePath );
	m_texture = cResourceManager::getInstance().getTexture( m_textureHandle );

}

///////////////////////////////////////////////////////////////////////////////////////

void cMaterial::load( void )
{

	m_vertSource.load( "assets/shaders/vert.shader" );
	m_fragSource.load( "assets/shaders/frag.shader" );

}

///////////////////////////////////////////////////////////////////////////////////////

void cMaterial::create( void )
{

	m_shader.create( m_vertSource, m_fragSource );

}

///////////////////////////////////////////////////////////////////////////////////////

void cMaterial::use( void )
{

	if ( m_hasTexture )
		m_texture->bind();

	m_shader.use();

}

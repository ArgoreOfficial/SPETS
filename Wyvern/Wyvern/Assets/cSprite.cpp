#include "cSprite.h"

#include <Wyvern/cApplication.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cSprite::cSprite( void )
{

}

cSprite::~cSprite( void )
{

}

///////////////////////////////////////////////////////////////////////////////////////

void cSprite::load( std::string _path )
{

	m_quad.vertices = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	};

	m_quad.indices = {
		0, 1, 2,
		3, 4, 5
	};

	m_quad.m_vertex_count = 6;

	m_material.loadTexture( _path );
	m_material.load();
	m_material.getTexture()->load( _path );

	m_texture_size.x = m_material.getTexture()->getWidth();
	m_texture_size.y = m_material.getTexture()->getHeight();

}

///////////////////////////////////////////////////////////////////////////////////////

void cSprite::create( void )
{

	m_material.create();
	m_quad.create();
	m_material.getTexture()->create();

}

///////////////////////////////////////////////////////////////////////////////////////

void cSprite::render( void )
{

	cApplication& app = cApplication::getInstance();
	cShaderProgram& shader = m_material.getShader();

	glm::mat4 model = glm::mat4( 1.0f );

	// float ysize = ( m_scale.y / m_scale.x ) / m_material.getTexture()->getAspect();
	model *= glm::translate( model, { m_position.x, m_position.y, m_position.z } );
	model *= glm::scale( model, { m_scale.x * m_texture_size.x, m_scale.y * m_texture_size.y, 1.0f } );

	m_material.use();

	shader.setUniform4f( "model",      model );
	shader.setUniform4f( "view",       app.getViewport().getActiveCamera()->getViewMatrix() );
	shader.setUniform4f( "projection", app.getViewport().getActiveCamera()->getProjMatrix() );
	
	m_quad.render();

}

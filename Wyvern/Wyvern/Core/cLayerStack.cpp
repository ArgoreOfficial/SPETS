#include "cLayerStack.h"

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cLayerStack::start( void )
{

	for ( size_t i = 0; i < m_layers.size(); i++ )
	{
		m_layers[ i ]->start();
	}

}

void cLayerStack::update( double _deltaTime )
{

	for ( size_t i = 0; i < m_layers.size(); i++ )
	{
		m_layers[ i ]->update( _deltaTime );
	}

}

void cLayerStack::draw3D( void )
{

	for ( size_t i = 0; i < m_layers.size(); i++ )
	{
		m_layers[ i ]->draw3D();
	}

}

void cLayerStack::draw2D( void )
{

	for ( size_t i = 0; i < m_layers.size(); i++ )
	{
		m_layers[ i ]->draw2D( );
	}

}

void cLayerStack::drawUI( void )
{

	for ( size_t i = 0; i < m_layers.size(); i++ )
	{
		m_layers[ i ]->drawUI();
	}

}


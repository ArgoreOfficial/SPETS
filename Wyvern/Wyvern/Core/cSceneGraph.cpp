#include "cSceneGraph.h"

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cSceneGraph::add( iSceneObject* _object )
{

	m_objects.push_back( _object );
	_object->setID( m_internalIDCount );
	m_internalIDCount++;
}

///////////////////////////////////////////////////////////////////////////////////////

void cSceneGraph::update( double _deltaTime )
{

	for ( size_t i = 0; i < m_objects.size(); i++ )
	{
		m_objects[ i ]->update( _deltaTime );
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void cSceneGraph::draw3D( void )
{

	for ( size_t i = 0; i < m_objects.size(); i++ )
	{
		m_objects[ i ]->draw3D();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void cSceneGraph::draw2D( void )
{

	for ( size_t i = 0; i < m_objects.size(); i++ )
	{
		m_objects[ i ]->draw2D();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void cSceneGraph::drawUI( void )
{

	for ( size_t i = 0; i < m_objects.size(); i++ )
	{
		m_objects[ i ]->drawUI();
	}

}

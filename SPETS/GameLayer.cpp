#include "GameLayer.h"

#include "cImportingWindow.h"

#include <Wyvern/Filesystem/cFilesystem.h>

#include <Wyvern/Renderer/Camera/cCamera2D.h>
#include <Wyvern/Renderer/Camera/cCamera3D.h>

///////////////////////////////////////////////////////////////////////////////////////

void GameLayer::start( void )
{

	wv::cApplication& app = wv::cApplication::getInstance();
	wv::cResourceManager& resm = wv::cResourceManager::getInstance();

	m_scene.add( new cImportingWindow() );
	
	m_camera3D = new wv::cCamera3D();
	m_camera2D = new wv::cCamera2D();

	m_camera3D->setFOV( 45.0f );
	m_camera3D->setPosition( { 0.0f, 0.0f, 3.0f } );
	
	app.getViewport().clear( wv::Color::Black );
	app.getViewport().setActiveCamera( m_camera2D );

} // start

///////////////////////////////////////////////////////////////////////////////////////

void GameLayer::update( double _deltaTime )
{

	wv::cApplication& app = wv::cApplication::getInstance();

	app.getScene().update( _deltaTime );

} // update

void GameLayer::draw3D( void )
{

	wv::cApplication::getInstance().getViewport().setActiveCamera( m_camera3D );

}

///////////////////////////////////////////////////////////////////////////////////////

void GameLayer::drawUI( void )
{
	ImGui::DockSpaceOverViewport();

	wv::cApplication::getInstance().getScene().drawUI();
	
} // drawUI

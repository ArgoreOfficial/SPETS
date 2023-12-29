#include "GameLayer.h"

#include <Wyvern/Renderer/Camera/cCamera2D.h>
#include <Wyvern/Renderer/Camera/cCamera3D.h>
#include <Wyvern/Managers/cResourceManager.h>

#include <imgui.h>
///////////////////////////////////////////////////////////////////////////////////////

void GameLayer::start( void )
{

	wv::cApplication& app = wv::cApplication::getInstance();
	wv::cResourceManager& resm = wv::cResourceManager::getInstance();

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

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos( viewport->Pos );
	ImGui::SetNextWindowSize( viewport->Size );

	if ( ImGui::Begin( "root", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration ) )
	{
		ImGui::BeginTabBar( "root_tab" );
		
		if ( ImGui::BeginTabItem( "Import" ) )
		{
			m_importingWindow.drawUI();
			ImGui::EndTabItem();
		}
		if ( ImGui::BeginTabItem( "Export" ) )
		{
			
			ImGui::EndTabItem();
		}


		ImGui::EndTabBar();
	}
	ImGui::End();

	wv::cApplication::getInstance().getScene().drawUI();
	
} // drawUI

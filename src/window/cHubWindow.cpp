#include "cHubWindow.h"

#include <imgui.h>

cHubWindow::cHubWindow( void )
{
	
}

cHubWindow::~cHubWindow( void )
{

}

void cHubWindow::onCreate( void )
{
	m_importing_window.onCreate();
}

void cHubWindow::onDestroy( void )
{
	m_importing_window.onDestroy();
}

void cHubWindow::drawWindow()
{
	if ( ImGui::Begin( "SPETS Tool Hub", &m_state, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking ) )
	{
		if ( ImGui::BeginTabBar( "HUB_BAR" ) )
		{
			if ( ImGui::BeginTabItem( "Blueprints" ) )
			{
				if ( ImGui::Button( "Import", { 100, 100 } ) )
					m_importing_window.toggle();

				ImGui::SameLine();
				ImGui::Button( "Export", { 100, 100 } );
				ImGui::SameLine();
				ImGui::Button( "Advanced", { 100, 100 } );
				ImGui::SameLine();
				ImGui::Button( "Edit", { 100, 100 } );
				
				ImGui::EndTabItem();
			}
			
			if ( ImGui::BeginTabItem( "Modding" ) )
			{
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();

		update();
	}
	ImGui::End();

	m_importing_window.draw();
}

#include "cHubWindow.h"

#include <imgui.h>

cHubWindow::cHubWindow( void ):
	m_import_button  ( "Import",   &m_importing_window, { "dae", "obj", "fbx", "gltf" } ),
	m_export_button  ( "Export",   nullptr, { "blueprint" } ),
	m_advanced_button( "Advanced", nullptr ),
	m_edit_button    ( "Edit",     nullptr )
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
	if ( ImGui::Begin( "SPETS Tool Hub", &m_is_open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking ) )
	{
		if ( ImGui::BeginTabBar( "HUB_BAR" ) )
		{
			if ( ImGui::BeginTabItem( "Blueprints" ) )
			{
				m_import_button.draw();
				ImGui::SameLine();
				m_export_button.draw();
				ImGui::SameLine();
				m_advanced_button.draw();
				ImGui::SameLine();
				m_edit_button.draw();

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

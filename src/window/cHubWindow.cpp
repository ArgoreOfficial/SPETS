#include "cHubWindow.h"

#include <imgui.h>

cHubWindow::cHubWindow( void )
{

}

cHubWindow::~cHubWindow( void )
{

}

void cHubWindow::drawWindow()
{
	if ( ImGui::Begin( "SPETS Tool Hub", 0, ImGuiWindowFlags_AlwaysAutoResize ) )
	{
		/* shoebox style */
		/*
		*/
		if ( ImGui::BeginTabBar( "HUB_BAR" ) )
		{
			if ( ImGui::BeginTabItem( "Blueprints" ) )
			{
				ImGui::Button( "Import", { 100, 100 } );
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
		
		/*
		if ( ImGui::BeginTabBar( "HUB_BAR" ) )
		{
			if ( ImGui::BeginTabItem( "Import" ) )
			{
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text( "Imagine there's like settings and shit here idfk" );

				ImGui::Button( "Load", { 60, 20 } );
				ImGui::SameLine();
				ImGui::Button( "Import", { 60, 20 } );

				ImGui::Spacing();
				ImGui::Text( "some more settings but in a different place tm" );

				ImGui::EndTabItem();
			}

			if ( ImGui::BeginTabItem( "Export" ) ) ImGui::EndTabItem();
			if ( ImGui::BeginTabItem( "Advanced" ) ) ImGui::EndTabItem();
			if ( ImGui::BeginTabItem( "Edit" ) ) ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		*/


		ImGui::End();
	}
}

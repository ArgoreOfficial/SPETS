#include "cImportingWindow.h"

#include <imgui.h>
#include <windows.h>
#include <shlobj.h>
#include <format>
#include <filesystem>

#pragma comment(lib, "shell32.lib")

cImportingWindow::cImportingWindow()
{

}

cImportingWindow::~cImportingWindow()
{

}

void cImportingWindow::onCreate( void )
{
	getFactions();

	m_selected_faction = "Default";
}

void cImportingWindow::onDestroy( void )
{
}

void cImportingWindow::drawWindow()
{
	if ( ImGui::Begin( "Import Blueprint", &m_is_open ) )
	{
		if ( ImGui::BeginCombo( "Faction", m_selected_faction.c_str() ) )
		{
			for ( int n = 0; n < m_factions.size(); n++ )
			{
				bool is_selected = ( m_selected_faction == m_factions[ n ] );

				if ( ImGui::Selectable( m_factions[ n ].c_str(), is_selected) )
					m_selected_faction = m_factions[ n ];
				if ( is_selected )
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}

		update();
	}
	ImGui::End();
}

void cImportingWindow::getFactions()
{
	CHAR my_documents[ MAX_PATH ];
	HRESULT result = SHGetFolderPathA( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents );

	std::string path = std::format( "{}\\My Games\\Sprocket\\Factions\\", my_documents );
	for ( auto& p : std::filesystem::directory_iterator( path ) )
	{
		if ( p.is_directory() )
		{
			m_factions.push_back( p.path().filename().string() );
			printf( "%s\n", p.path().filename().string().c_str() );
		}

	}
	
	/* My Games\Sprocket\Factions */
}

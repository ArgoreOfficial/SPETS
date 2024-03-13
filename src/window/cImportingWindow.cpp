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
	m_selected_faction = m_factions[ 0 ];
}

void cImportingWindow::onDestroy( void )
{
}

void cImportingWindow::drawWindow()
{
	if ( ImGui::Begin( "Import Blueprint" ) )
	{
		update();

		if ( ImGui::BeginCombo( "Faction", m_selected_faction.c_str() ) ) // The second parameter is the label previewed before opening the combo.
		{
			for ( int n = 0; n < m_factions.size(); n++ )
			{
				bool is_selected = ( m_selected_faction == m_factions[ n ] ); // You can store your selection however you want, outside or inside your objects

				if ( ImGui::Selectable( m_factions[ n ].c_str(), is_selected) )
					m_selected_faction = m_factions[ n ];
				if ( is_selected )
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

			}
			ImGui::EndCombo();
		}

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

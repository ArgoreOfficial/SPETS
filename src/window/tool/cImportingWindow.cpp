#include "cImportingWindow.h"

#include <tools/importer/cMeshImporter.h>

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
	m_width = 300;
	m_height = 200;
}

void cImportingWindow::onDestroy( void )
{
}

void cImportingWindow::drawWindow()
{
	if ( ImGui::Begin( "Import Blueprint", &m_is_open, ImGuiWindowFlags_NoResize ) )
	{
		ImGui::Text( "File: %s", m_filename.c_str() );

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

		ImGui::BeginDisabled(); // TODO: implement merging
		ImGui::Checkbox( "Merge Compartments(wip)", &m_merge_compartments );
		ImGui::EndDisabled();

		ImGui::Checkbox( "Import as Vehicle(not finished)", &m_import_as_vehicle );

		if ( ImGui::Button( "Import" ) )
			importMesh();

		update();
	}
	ImGui::End();
}

void cImportingWindow::getFactions()
{
	CHAR my_documents[ MAX_PATH ];
	HRESULT result = SHGetFolderPathA( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents );

	m_factions_dir = std::format( "{}\\My Games\\Sprocket\\Factions\\", my_documents );
	for ( auto& p : std::filesystem::directory_iterator( m_factions_dir ) )
	{
		if ( p.is_directory() )
		{
			std::string faction( reinterpret_cast<const char*>( p.path().filename().u8string().c_str() ) );
			m_factions.push_back( faction );
		}
	}
}

void cImportingWindow::importMesh()
{
	
	int flags = 0;
	flags |= MeshImporterFlags_MergeCompartments * (int)m_merge_compartments;
	flags |= MeshImporterFlags_ImportAsVehicle   * (int)m_import_as_vehicle;

	std::string outpath = m_factions_dir + m_selected_faction + "\\Blueprints\\";
	outpath            += m_import_as_vehicle ? "Vehicles\\" : "Compartments\\";

	cMeshImporter importer( m_file_path, outpath, (eMeshImporterFlags)flags);
	
}

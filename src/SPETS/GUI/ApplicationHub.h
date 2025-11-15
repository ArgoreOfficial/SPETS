#pragma once

#include <wx/wx.h>
#include <wx/dnd.h>

#include <SPETS/Util.h>
#include <SPETS/GUI/Tools/ImportTool.h>
#include <SPETS/GUI/Tools/ExportTool.h>

#include <Sprocket/Sprocket.h>

#include <filesystem>

namespace SPETS {

class ApplicationHubFrame : public wxFrame
{
public:
	ApplicationHubFrame();

	void onDropFiles( const std::vector<std::filesystem::path>& _paths );

private:
	void OnAbout( wxCommandEvent& event ) {
		std::string version = "SPETS Version: ";
		version += SPETS::VERSION_STR;
		wxMessageBox( version, "About SPETS", wxOK | wxICON_INFORMATION );
	}

	void OnExit( wxCommandEvent& event ) {
		Close( true );

		delete m_importTool;
		delete m_exportTool;
	}

	void OnQuickImport( wxCommandEvent& _event );

	void OnQuickExport( wxCommandEvent& _event ) { 
		if( m_importTool ) 
			m_importTool->onRunTool(); 
	}

	void OnMerge( wxCommandEvent& event );

	wxPanel* m_panel = new wxPanel( this );
	ImportTool* m_importTool = nullptr;
	ExportTool* m_exportTool = nullptr;

};

extern ApplicationHubFrame* g_frame;

class Application : public wxApp
{
	bool OnInit() override { 
		g_frame = new ApplicationHubFrame();
		return g_frame->Show(); 
	}
};

}

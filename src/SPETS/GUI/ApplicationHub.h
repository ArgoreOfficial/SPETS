#pragma once

#include <wx/wx.h>
#include <wx/dnd.h>

#include <SPETS/Util.h>

#include <Sprocket/Sprocket.h>

#include <filesystem>

namespace SPETS {

class ApplicationHubFrame : public wxFrame
{
public:
	ApplicationHubFrame();

private:
	void OnAbout( wxCommandEvent& event ) {
		std::string version = "SPETS Version: ";
		version += SPETS::VERSION_STR;
		wxMessageBox( version, "About SPETS", wxOK | wxICON_INFORMATION );
	}

	void OnExit( wxCommandEvent& event ) {
		Close( true );
	}

	void OnQuickImport( wxCommandEvent& _event );
	void OnQuickExport( wxCommandEvent& _event );

	void OnHoverImport( wxMouseEvent& _event ) {
		printf( "%s\n", _event.Dragging() ? "true" : "false" );
	}

	void OnMerge( wxCommandEvent& event ) {
		wxLogMessage( "Work in progress." );
	}

	wxPanel*  m_panel             = new wxPanel( this );
	
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

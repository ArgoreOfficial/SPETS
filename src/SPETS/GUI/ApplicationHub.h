#pragma once

#include <wx/wx.h>
#include <wx/dnd.h>

#include <SPETS/Util.h>
#include <Sprocket/Sprocket.h>

#include <filesystem>

namespace SPETS {



class HubWindowDropTarget : public wxFileDropTarget
{
public:
	HubWindowDropTarget( wxStaticBitmap* _surface, wxBitmap _bitmap, wxBitmap _bitmapHover )
		: wxFileDropTarget{},
		m_surface{ _surface },
		m_bitmap{ _bitmap },
		m_bitmapHover{ _bitmapHover }
	{ 
		_surface->SetBitmap( _bitmap );
	};

	// Inherited via wxFileDropTarget
	bool OnDropFiles( wxCoord _x, wxCoord _y, const wxArrayString& _filenames ) override;

	virtual wxDragResult OnEnter( wxCoord _x, wxCoord _y, wxDragResult _defResult ) {
		if ( m_surface )
			m_surface->SetBitmap( m_bitmapHover );
		return wxDragResult::wxDragMove;
	}

	virtual void OnLeave() {
		if ( m_surface )
			m_surface->SetBitmap( m_bitmap );
	}
	
private:
	wxStaticBitmap* m_surface = nullptr;
	wxBitmap m_bitmap;
	wxBitmap m_bitmapHover;
};

class Frame : public wxFrame
{
public:
	Frame();

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

extern Frame* g_frame;

class Application : public wxApp
{
	bool OnInit() override { 
		g_frame = new Frame();
		return g_frame->Show(); 
	}
};

}

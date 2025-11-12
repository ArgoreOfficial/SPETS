#pragma once

#include <wx/wx.h>
#include <wx/dnd.h>

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

	// implemented in ApplicationHub.cpp
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

}
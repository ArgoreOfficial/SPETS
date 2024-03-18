#include "cToolButton.h"
#include "iToolWindow.h"

#include <Windows.h>
#include <core/cApplication.h>

#include <imgui.h>

cToolButton::cToolButton( std::string _text, iToolWindow* _tool_window, std::vector<std::string> _allowed_extensions ):
	m_text              { _text },
	m_allowed_extensions{ _allowed_extensions },
	m_tool_window       { _tool_window }
{
	m_hover_interpolator.setDuration( 0.1f );
}

cToolButton::~cToolButton()
{
}

void cToolButton::draw()
{
	cApplication& app = *cApplication::getInstance();

	const int width = 100;
	const int height = 100;

	bool button_enabled = false;
	if( m_tool_window ) 
		button_enabled = !m_tool_window->getState();
	
	if ( ImGui::BeginChild( ( m_text + "_frame" ).c_str(), { width, height } ) )
	{
		std::string text = m_text;
		if ( button_enabled && m_hovering )
			text = app.getDragDropSurface().isDraggingFile() ? m_on_drag_hover_text : m_on_hover_text;

		sPoint<int> mouse_pos = cApplication::getInstance()->getCursorPosition();
		ImVec2 w_pos = ImGui::GetWindowPos();
		sPoint<int> min = { (int)w_pos.x, (int)w_pos.y };
		sPoint<int> max = { min.x + width, min.y + height };

		bool hovering = mouse_pos.intersectsRect( min, max );

		float t = updateHoveringT( hovering );
		float padding = t * 7.0f;
		m_hovering = hovering;

		if ( button_enabled )
		{	
			checkClick   ( hovering );
			checkDragDrop( hovering );
		}

		drawButton( text, width, height, padding, t, button_enabled );
	}
	ImGui::EndChild();
}

float cToolButton::updateHoveringT( bool _hovering )
{
	m_hover_interpolator.update( ImGui::GetIO().DeltaTime );

	if ( _hovering != m_hovering )
		m_hover_interpolator.setProgress( 0.0f );

	float t = m_hover_interpolator.getProgress();
	if ( _hovering )
		t = 1.0f - t;

	return t;
}

void cToolButton::checkClick( bool _hovering )
{
	cApplication& app = *cApplication::getInstance();

	if ( app.wasMouseJustDown() )
		m_mouse_down_on = _hovering;

	if ( !app.wasMouseJustUp() )
		return;
	if ( !m_mouse_down_on )
		return;
	if ( m_allowed_extensions.empty() )
		return;

	std::string path = openFileDialog();		
	if ( path == "" )
		return;

	if ( m_tool_window )
	{
		m_tool_window->open();
		m_tool_window->loadFile( path );
	}
}

void cToolButton::checkDragDrop( bool _hovering )
{
	if ( !_hovering )
		return;

	cApplication& app = *cApplication::getInstance();
	std::vector<std::string>& dropped_files = app.getDragDropSurface().getDroppedPaths();

	if ( dropped_files.empty() )
		return;

	if ( !m_allowed_extensions.empty() )
	{
		// open file
		std::string extension = dropped_files[ 0 ].substr( dropped_files[ 0 ].find_last_of( "." ) + 1 );
		for ( int i = 0; i < m_allowed_extensions.size(); i++ )
		{
			if ( m_allowed_extensions[ i ] == extension )
			{
				if ( m_tool_window )
				{
					m_tool_window->open();
					m_tool_window->loadFile( dropped_files[ 0 ] );
				}
				break;
			}
		}
	}
	else if( m_tool_window )
		m_tool_window->open();
	
	dropped_files.clear();
}

void cToolButton::drawButton( std::string _text, int _width, int _height, float _padding, float _t, bool _enabled )
{
	if ( !_enabled )
		ImGui::BeginDisabled();

	if ( _enabled )
	{
		// draw custom outline
		float padded_w = (float)_width  - _padding * 2;
		float padded_h = (float)_height - _padding * 2;

		ImGui::SetCursorPos( { _padding, _padding } );
		
		ImGui::SetNextWindowBgAlpha( 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, 1.0f - _t );
		ImGui::BeginChild( ( _text + "_frame_outline" ).c_str(), { padded_w, padded_h }, true );
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	ImVec2 button_size = ImGui::GetWindowSize();
	ImVec2 text_size = ImGui::CalcTextSize( _text.c_str() );

	ImGui::SetCursorPosX( ( button_size.x - text_size.x ) * 0.5f );
	ImGui::SetCursorPosY( ( button_size.y - text_size.y ) * 0.5f );
	ImGui::Text( _text.c_str() );

	if ( !_enabled )
		ImGui::EndDisabled();
}

std::string cToolButton::openFileDialog( void )
{
	// common dialog box structure, setting all fields to 0 is important
	TCHAR szFile[ 260 ] = { 0 };
	// Initialize remaining fields of OPENFILENAME structure
	OPENFILENAME ofn = {
		.lStructSize = sizeof( ofn ),
		.hwndOwner = cApplication::getInstance()->getWindow().getWin32Handle(),
		.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0",
		.nFilterIndex = 1,
		.lpstrFile = szFile,
		.nMaxFile = sizeof( szFile ),
		.lpstrFileTitle = NULL,
		.nMaxFileTitle = 0,
		.lpstrInitialDir = NULL,
		.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
	};

	if ( GetOpenFileName( &ofn ) == TRUE )
		return std::string( CW2A( ofn.lpstrFile ) );
	else
		return "";
}

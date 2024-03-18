#include "cToolButton.h"
#include "iToolWindow.h"

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

	if ( ImGui::BeginChild( ( m_text + "_frame" ).c_str(), { width, height } ) )
	{
		sPoint<int> mouse_pos = cApplication::getInstance()->getCursorPosition();
		ImVec2 w_pos = ImGui::GetWindowPos();
		sPoint<int> min = { (int)w_pos.x, (int)w_pos.y };
		sPoint<int> max = { min.x + width, min.y + height };

		bool hovering = mouse_pos.intersectsRect( min, max );
		std::string text = hovering ? m_on_hover_text : m_text;
		
		if ( app.wasMouseJustDown() )
			m_mouse_down_on = hovering;
		
		if ( app.wasMouseJustUp() )
		{
			if ( m_mouse_down_on )
			{
				m_tool_window->open();
				if ( !m_allowed_extensions.empty() )
				{
					// open file
					m_tool_window->loadFile( "" );
				}
			}
		}

		m_hover_interpolator.update( ImGui::GetIO().DeltaTime );

		if ( hovering != m_hovering )
			m_hover_interpolator.setProgress( 0.0f );

		float t = m_hover_interpolator.getProgress();
		if ( hovering )
			t = 1.0f - t;

		float padding = t * 7.0f;
		float padded_w = (float)width - padding * 2;
		float padded_h = (float)height - padding * 2;

		ImGui::SetCursorPos( { padding, padding } );
		
		// draw custom outline
		ImGui::SetNextWindowBgAlpha( 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, 1.0f - t );
		ImGui::BeginChild( ( text + "_frame_outline" ).c_str(), { padded_w, padded_h }, true );
		ImGui::EndChild();
		ImGui::PopStyleVar();
		
		ImVec2 button_size = ImGui::GetWindowSize();
		ImVec2 text_size = ImGui::CalcTextSize( text.c_str() );
		
		ImGui::SetCursorPosX( ( button_size.x - text_size.x ) * 0.5f );
		ImGui::SetCursorPosY( ( button_size.y - text_size.y ) * 0.5f );
		ImGui::Text( text.c_str() );

		m_hovering = hovering;
	}
	ImGui::EndChild();
}

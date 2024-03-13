#include "iWindow.h"

#include <core/cApplication.h>

void iWindow::draw( void )
{
	float t = static_cast<float>( m_state );

	if ( m_popup_interpolator.getProgress() < 1.0f )
	{
		m_popup_interpolator.update( ImGui::GetIO().DeltaTime );

		t = m_popup_interpolator.easeOutExpo();
		if ( !m_state )
			t = 1.0f - t;

		float fade_pad_width = m_width_fade_amount - m_width_fade_amount * t;
		float fade_pad_height = m_height_fade_amount - m_height_fade_amount * t;

		ImVec2 pos = m_saved_window_pos;
		pos.x += fade_pad_width / 2;
		pos.y += fade_pad_height / 2;
		ImGui::SetNextWindowPos( pos );
		ImGui::SetNextWindowSize( { m_width - fade_pad_width, m_height - fade_pad_height } );
	}

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha, t );

	if ( m_just_opened )
	{
		m_just_opened = false;
		ImGui::SetNextWindowFocus();
	}

	drawWindow();
	ImGui::PopStyleVar();

}

void iWindow::open( void )
{
	m_state = true;
	m_just_opened = true;
	m_popup_interpolator.setProgress( 0.0f );
	m_popup_interpolator.setDuration( 0.5f );
}

void iWindow::close( void )
{
	m_state = false;
	m_popup_interpolator.setProgress( 0.0f );
	m_popup_interpolator.setDuration( 0.2f );

	m_saved_window_pos = m_last_window_pos;
}

void iWindow::toggle( void )
{
	if ( m_state )
		close();
	else
		open();
}

void iWindow::forceToggle( void )
{
	forceState( !m_state );
	m_popup_interpolator.setProgress( static_cast<float>( m_state ) );
}

void iWindow::update()
{
	m_last_window_pos = ImGui::GetWindowPos();

	int min_x = m_last_window_pos.x;
	int min_y = m_last_window_pos.y;
	int max_x = std::max( min_x + ImGui::GetWindowSize().x, ImGui::GetWindowSize().x );
	int max_y = std::max( min_y + ImGui::GetWindowSize().y, ImGui::GetWindowSize().y );

	ImVec2 mouse_pos = ImGui::GetMousePos();
	bool hovering = ( mouse_pos.x >= min_x && mouse_pos.x < max_x &&
		              mouse_pos.y >= min_y && mouse_pos.y < max_y );

	cApplication::getInstance()->checkScreenBounds( min_x, min_y, max_x, max_y, hovering );
}


#include "iWindow.h"

#include <core/cApplication.h>

void iWindow::draw( void )
{
	float t = static_cast<float>( m_internal_state );

	if ( m_popup_interpolator.getProgress() < 1.0f )
	{
		m_popup_interpolator.update( ImGui::GetIO().DeltaTime );

		t = m_popup_interpolator.easeOutExpo();
		if ( !m_internal_state )
			t = 1.0f - t;

		float width_scaling  = m_width_fade_amount  * m_width;
		float height_scaling = m_height_fade_amount * m_height;

		float fade_pad_width  = width_scaling  - ( width_scaling  * t );
		float fade_pad_height = height_scaling - ( height_scaling * t );

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
	if ( m_internal_state || m_popup_interpolator.getProgress() != 1.0f )
		return;

	m_internal_state = true;
	m_is_open = true;
	m_just_opened = true;
	m_popup_interpolator.setProgress( 0.0f );
	m_popup_interpolator.setDuration( 0.5f );
}

void iWindow::close( void )
{
	if ( !m_internal_state || m_popup_interpolator.getProgress() != 1.0f )
		return;

	m_internal_state = false;
	m_is_open = false;
	m_popup_interpolator.setProgress( 0.0f );
	m_popup_interpolator.setDuration( 0.5f );

	m_saved_window_pos = m_last_window_pos;
}

void iWindow::toggle( void )
{
	if ( m_internal_state )
		close();
	else
		open();
}

void iWindow::forceToggle( void )
{
	forceState( !m_internal_state );
	m_popup_interpolator.setProgress( static_cast<float>( m_internal_state ) );
}

void iWindow::forceState( bool _state )
{
	m_internal_state = _state; 
	m_is_open = _state;
	m_just_opened = m_internal_state;
};

void iWindow::update()
{
	cApplication& application = *cApplication::getInstance();

	m_last_window_pos = ImGui::GetWindowPos();

	sPoint<int> min = {
		m_last_window_pos.x,
		m_last_window_pos.y
	};

	sPoint<int> max = {
		std::max( min.x + ImGui::GetWindowSize().x, ImGui::GetWindowSize().x ),
		std::max( min.y + ImGui::GetWindowSize().y, ImGui::GetWindowSize().y )
	};
	
	sPoint<int> mouse_pos = application.getCursorPosition();
	bool hovering = mouse_pos.intersectsRect( min, max );

	application.checkScreenBounds( min.x, min.y, max.x, max.y, hovering );

	if ( m_is_open != m_internal_state )
	{
		close();
		m_is_open = m_internal_state;
	}
}


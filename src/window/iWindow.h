#pragma once

#include <defines.h>
#include <imgui.h>

#include <math/cInterpolator.h>

class iWindow
{
	DECLARE_INTERFACE( iWindow )

public:

	void draw( void );

	void open       ( void );
	void close      ( void );
	void toggle     ( void );
	void forceToggle( void );
	
	void forceState( bool _state );
	bool getState  ( void ) { return m_internal_state; };

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

protected:

	virtual void drawWindow() = 0;

	void update();

	bool m_is_open = false;
	
	float m_width = 400;
	float m_height = 400;
	float m_width_fade_amount = 40;
	float m_height_fade_amount = 40;

private:
	bool m_internal_state = false;

	bool m_just_opened = false;

	cInterpolator m_popup_interpolator;
	ImVec2 m_last_window_pos{ 700, 300 };
	ImVec2 m_saved_window_pos{ 700, 300 };
};

#pragma once

#include "cWindow.h"
#include "cRenderer.h"
#include <string>

#include <window/cHubWindow.h>

#include <window/cDragDropSurface.h>

template<typename T>
struct sPoint 
{ 
	T x, y; 
	bool intersectsRect( sPoint<T> _min, sPoint<T> _max )
	{
		return ( x >= _min.x && x < _max.x && y >= _min.y && y < _max.y );
	}
};

class cApplication
{

public:
	 cApplication();
	~cApplication();

	void start();
	void run();
	void shutdown();

	std::string getVersion();

	static cApplication* getInstance()
	{
		static cApplication* instance = nullptr;
		if ( !instance )
			instance = new cApplication();

		return instance;
	}

	void checkScreenBounds( int _min_x, int _min_y, int _max_x, int _max_y, bool _hovering );
	
	cDragDropSurface& getDragDropSurface( void ) { return m_drag_drop_surface; }
	sPoint<int>       getCursorPosition ( void ) { return m_cursor_pos; }
	bool              getLMouseState    ( void ) { return m_lmouse_state; }

	bool              wasMouseJustDown  ( void ) { return  m_lmouse_state && !m_lmouse_state_prev; }
	bool              wasMouseJustUp    ( void ) { return !m_lmouse_state &&  m_lmouse_state_prev; }

	cWindow& getWindow( void ) { return m_window; }

private:

	void resetScreenBounds();

	struct sVersion
	{
		char type;
		int major;
		int minor;
		int year;
		int revision;
	};

	cWindow          m_window;
	cRenderer        m_renderer;
	cHubWindow       m_hub_window;
	cDragDropSurface m_drag_drop_surface;

	cApplication::sVersion m_version;

	// input state
	sPoint<int> m_cursor_pos;
	bool m_lmouse_state      = false;
	bool m_lmouse_state_prev = false;

	int m_min_x = 0;
	int m_min_y = 0;
	int m_max_x = 0;
	int m_max_y = 0;
	bool m_hovering = false;
};
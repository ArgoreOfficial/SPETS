#include "cApplication.h"

#include <format>



cApplication::cApplication()
{
#if defined DEBUG
	char type = 'd';
#elif defined RELEASE
	char type = 'p';
#elif defined FINAL
	char type = 'r';
#endif

	m_version = {
		.type     = type,
		.major    = 2,
		.minor    = 0,
		.year     = 24,
		.revision = 0,
	};

}

cApplication::~cApplication()
{

}

void cApplication::start()
{
	std::string title = std::format( "SPETS {}", getVersion() );
	m_window.create( 300, 300, title.c_str() );
	m_renderer.create( m_window );

	m_hub_window.onCreate();
	m_hub_window.forceState( true );
	
	resetScreenBounds();

	HRESULT drag_drop_result = RegisterDragDrop( m_window.getWin32Handle(), &m_hub_window );
	switch ( drag_drop_result )
	{
	case DRAGDROP_E_INVALIDHWND:       printf( "DRAGDROP_E_INVALIDHWND\n" ); break;
	case DRAGDROP_E_ALREADYREGISTERED: printf( "DRAGDROP_E_ALREADYREGISTERED\n" ); break;
	case E_OUTOFMEMORY:                printf( "E_OUTOFMEMORY\n" ); break;
	}
}

void cApplication::run()
{
	while ( !m_window.shouldClose() && m_hub_window.getState() )
	{

		/*
		 * winapi is used here because imgui doesn't update
		 * mouse position if another window has focus
		 */
		POINT mouse_pos;
		GetCursorPos( &mouse_pos );
		m_cursor_pos.x = mouse_pos.x;
		m_cursor_pos.y = mouse_pos.y;

		m_lmouse_state_prev = m_lmouse_state;
		m_lmouse_state = GetAsyncKeyState( VK_LBUTTON ) & 0x10000; // should definitely be an event but whatever

		m_window.beginFrame();
		m_renderer.beginFrame();


		resetScreenBounds();
		
		m_renderer.clear( 0x00000000 );
		
		m_hub_window.draw();

		glfwSetWindowAttrib( m_window.getWindowObject(), GLFW_MOUSE_PASSTHROUGH, !m_hovering );
		
		m_renderer.endFrame();
		m_window.endFrame();

		
		m_window.setSize( m_max_x + 20, m_max_y + 20 );

	}
}

void cApplication::shutdown()
{
	m_hub_window.onDestroy();

	m_renderer.destroy();
	m_window.destroy();
}

std::string cApplication::getVersion()
{
	return std::format( "{}{}.{}-{}.{}", m_version.type, m_version.major, m_version.minor, m_version.year, m_version.revision );
}

void cApplication::checkScreenBounds( int _min_x, int _min_y, int _max_x, int _max_y, bool _hovering )
{
	if ( _min_x < m_min_x ) m_min_x = _min_x;
	if ( _min_y < m_min_y ) m_min_y = _min_y;

	if ( _max_x > m_max_x ) m_max_x = _max_x;
	if ( _max_y > m_max_y ) m_max_y = _max_y;

	if ( _hovering ) m_hovering = true;
}

void cApplication::resetScreenBounds()
{
	m_min_x = INT32_MAX;
	m_min_y = INT32_MAX;
	m_max_x = INT32_MIN;
	m_max_y = INT32_MIN;
	m_hovering = false;
}

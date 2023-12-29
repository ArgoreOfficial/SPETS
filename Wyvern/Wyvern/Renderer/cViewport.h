#pragma once

#if defined( WV_PLATFORM_WINDOWS ) || defined( WV_PLATFORM_WINDOWS_32 ) || defined( WV_PLATFORM_LINUX ) || defined( WV_PLATFORM_MAC )
#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#endif

#include <Wyvern/Logging/cLogging.h>
#include <Wyvern/Misc/cColor.h>
#include <Wyvern/Renderer/Camera/iCamera.h>

#include <string>



///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cViewport
	{

	public:

		enum class eViewportState
		{
			kOpen,
			kFocused,
			kMinimized,
			kClosing
		};

		 cViewport();
		~cViewport();

///////////////////////////////////////////////////////////////////////////////////////

		void create       ( std::string _title, unsigned int _width, unsigned int _height );
		void destroy      ( void );
		void initImguiImpl( void );
		void hookEvents   ( void );

///////////////////////////////////////////////////////////////////////////////////////

		void setTitle       ( const std::string& _title );
		void setVSync       ( bool _value );
		void setFullscreen  ( bool _value );
		void setClearColor  ( cColor _color )    { m_clearColor = _color; }
		void setActiveCamera( iCamera* _camera ) { m_activeCamera = _camera; }

///////////////////////////////////////////////////////////////////////////////////////

		unsigned int   getWidth        ( void ) { return m_viewWidth; }
		unsigned int   getHeight       ( void ) { return m_viewHeight; }
		eViewportState getState        ( void ) { return m_state; }
		iCamera*       getActiveCamera ( void ) { return m_activeCamera; }
		float          getAspect       ( void ) { return (float)m_viewWidth / (float)m_viewHeight; }

///////////////////////////////////////////////////////////////////////////////////////

		void processInput( void );
		void update      ( void );
		void display     ( void );
		void clear       ( const cColor& _color );
		void clear       ( void ) { clear( m_clearColor ); }

///////////////////////////////////////////////////////////////////////////////////////

	private:

	#if defined( WV_PLATFORM_WINDOWS ) || defined( WV_PLATFORM_WINDOWS_32 ) || defined( WV_PLATFORM_LINUX ) || defined( WV_PLATFORM_MAC )
		GLFWwindow* m_window = nullptr;
	#endif
		
		eViewportState m_state  = eViewportState::kOpen;
		iCamera* m_activeCamera = nullptr;
		cColor m_clearColor     = Color::PacificBlue;
		int m_viewWidth         = 0;
		int m_viewHeight        = 0;

	};

///////////////////////////////////////////////////////////////////////////////////////

}
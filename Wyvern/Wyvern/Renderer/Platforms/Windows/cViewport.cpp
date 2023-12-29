#include <Wyvern/Renderer/cViewport.h>
#include <Wyvern/Managers/cEventManager.h>
#include <Wyvern/cApplication.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cViewport::cViewport()
{

}

///////////////////////////////////////////////////////////////////////////////////////

cViewport::~cViewport()
{

}

///////////////////////////////////////////////////////////////////////////////////////

void onResize( GLFWwindow* _window, int _width, int _height )
{

	auto& viewport = cApplication::getInstance().getViewport();
	glViewport( 0, 0, _width, _height );
	viewport.getActiveCamera()->setAspect( (float)_width / (float)_height );

}

///////////////////////////////////////////////////////////////////////////////////////

void handleApplicationEvents()
{

}

///////////////////////////////////////////////////////////////////////////////////////

void handleKeyEvents( GLFWwindow* window, int key, int scancode, int action, int mods )
{

	Events::cKeyEvent keyEvent( key );
	cEventManager::call<Events::cKeyEvent>( keyEvent );

	if ( action == GLFW_PRESS )
	{

		Events::cKeyDownEvent downEvent( key );
		cEventManager::call<Events::cKeyDownEvent>( downEvent );

	}
	else if ( action == GLFW_RELEASE )
	{

		Events::cKeyUpEvent upEvent( key );
		cEventManager::call<Events::cKeyUpEvent>( upEvent );

	}

}

///////////////////////////////////////////////////////////////////////////////////////

void handleMouseEvents( GLFWwindow* window, double xpos, double ypos )
{

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::create( std::string _title, unsigned int _width, unsigned int _height )
{

	WV_DEBUG( "Creating Window [%i, %i]", _width, _height );

	if ( !glfwInit() )
	{

		WV_FATAL( "GLFW could not initialize!" );
		glfwTerminate();
		return;

	}
	WV_DEBUG( "GLFW Initialized" );

	m_window = glfwCreateWindow( _width, _height, _title.c_str(), nullptr, nullptr);
	
	if ( !m_window )
	{

		WV_FATAL( "Failed to create GLFW window" );
		glfwTerminate();
		return;

	}
	WV_DEBUG( "GLFW Window created" );

	glfwSetFramebufferSizeCallback( m_window, onResize );
	glfwMakeContextCurrent( m_window );
	gladLoadGL( glfwGetProcAddress );

	hookEvents();

	glfwGetFramebufferSize( m_window, &m_viewWidth, &m_viewHeight );

	// move to backend.init() or something

	glEnable( GL_DEPTH_TEST );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::destroy()
{

	WV_DEBUG( "Terminated GLFW" );
	glfwTerminate();

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::initImguiImpl()
{

	ImGui_ImplGlfw_InitForOpenGL( m_window, true );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::hookEvents()
{

	glfwSetKeyCallback( m_window, handleKeyEvents );
	glfwSetCursorPosCallback( m_window, handleMouseEvents );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::setTitle( const std::string& _title )
{

	glfwSetWindowTitle( m_window, _title.c_str() );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::setVSync( bool _value )
{

	glfwSwapInterval( _value ? 1 : 0 );

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::cViewport::setFullscreen( bool _value )
{

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::update()
{

	glfwGetFramebufferSize( m_window, &m_viewWidth, &m_viewHeight );

	processInput();
	if ( glfwWindowShouldClose( m_window ) )
	{

		m_state = eViewportState::kClosing;
		WV_DEBUG( "Closing" );

	}

	glfwPollEvents();

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::clear( const cColor& _color )
{

	m_clearColor = _color;

	const float red   = ( float )( _color.r ) / 255.0f;
	const float green = ( float )( _color.g ) / 255.0f;
	const float blue  = ( float )( _color.b ) / 255.0f;
	const float alpha = ( float )( _color.a ) / 255.0f;
	
	glClearColor( red, green, blue, alpha );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::display()
{

	glfwSwapBuffers( m_window );

}

///////////////////////////////////////////////////////////////////////////////////////

void cViewport::processInput()
{

	if ( glfwGetKey( m_window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) // escape exit
	{

		m_state = eViewportState::kClosing;
		glfwSetWindowShouldClose( m_window, true );

	}

}

///////////////////////////////////////////////////////////////////////////////////////

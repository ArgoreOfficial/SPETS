#include "cApplication.h"

#include <Wyvern/Core/iLayer.h>
#include <Wyvern/Core/cLayerStack.h>
#include <Wyvern/Logging/cLogging.h>
#include <Wyvern/Managers/cResourceManager.h>

#include <Wyvern/Renderer/Framework/cShaderProgram.h>
#include <Wyvern/Assets/cShaderSource.h>
#include <Wyvern/Assets/cModel.h>
#include <Wyvern/Assets/cSprite.h>

#include <thread>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::run( void )
{

	///////// START ///////// 

	if ( !create() )
	{
		WV_FATAL( "Application could not be created!" );
		return;
	}

	// if( imguiEnabled )
	initImgui();

	m_layerStack.start();

	m_viewport.getActiveCamera()->update();

	startLoadThread();
	cResourceManager::getInstance().createResources();

	///////// RUN LOOP ///////// 

	m_lastTime = 0.0;
	bool run = true;

	// select draw mode, move to renderer
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // wireframe
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // default

	while ( run )
	{

		update();
		m_viewport.getActiveCamera()->update();

		draw();

		if ( m_viewport.getState() == cViewport::eViewportState::kClosing )
			run = false;

	}

	///////// CLOSE ///////// 

	destroy();

}

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::startLoadThread( void )
{
	auto& resourceManager = cResourceManager::getInstance();

	std::thread* loadthread = resourceManager.loadResources();
	double loadtimer = glfwGetTime();

	m_viewport.setClearColor( wv::Color::Black );

	cSprite* loadingSprite = new cSprite();
	loadingSprite->load( "assets/textures/loading.png" );
	loadingSprite->create();

	while ( resourceManager.isLoading() )
	{
		m_time = glfwGetTime();
		m_deltaTime = m_time - m_lastTime;
		m_lastTime = m_time;
		
		m_viewport.clear();
		
		std::string title = "Loading... " + std::to_string( 1.0f / m_deltaTime );
		m_viewport.setTitle( title.c_str() );
		
		m_viewport.update();

		loadingSprite->render();

		m_viewport.display();
	}

	loadthread->join();
	WV_DEBUG( "Loading took %.5f seconds", ( glfwGetTime() - loadtimer ) );

	delete loadingSprite;

}

///////////////////////////////////////////////////////////////////////////////////////

int cApplication::create( void )
{

	int major = 0;
	int minor = 3;

	WV_INFO( "Loading Wyvern runtime version %i.%i", major, minor );

	m_viewport.create( "Wyvern", 640, 480 );

	return 1;

}

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::destroy( void )
{
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown(); // move to viewport
	ImGui::DestroyContext();
	
	m_viewport.destroy();

}

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::initImgui( void )
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	WV_DEBUG( "ImGui Context Created" );

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enavbe Viewports
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
	{
		style.WindowRounding = 0.0f;
		style.Colors[ ImGuiCol_WindowBg ].w = 1.0f;
	}
	

	// should prbably be moved out somewhere else
	m_viewport.initImguiImpl();
	ImGui_ImplOpenGL3_Init();
	WV_DEBUG( "ImGui_ImplOpenGL3_Init()" );

}

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::update( void )
{
	m_time = glfwGetTime();
	m_deltaTime = m_time - m_lastTime;
	m_lastTime = m_time;

	std::string title = "Wyvern " + std::to_string( 1.0f / m_deltaTime );
	m_viewport.setTitle(title.c_str());

	m_viewport.update();

	m_layerStack.update( m_deltaTime );
}

///////////////////////////////////////////////////////////////////////////////////////

void cApplication::draw( void )
{
	ImGuiIO& io = ImGui::GetIO();;
	
	m_layerStack.draw3D();

	m_layerStack.draw2D();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	m_layerStack.drawUI();
	
	// move most of this out somewhere
	ImGui::Render();
	int width = m_viewport.getWidth();
	int height = m_viewport.getHeight();

	glViewport( 0, 0, width, height );
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent( backup_current_context );
	}
	
	m_viewport.display();

}


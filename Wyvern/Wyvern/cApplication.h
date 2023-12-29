#pragma once

#include <Wyvern/Core/cLayerStack.h>
#include <Wyvern/Core/cSceneGraph.h>
#include <Wyvern/Core/iSingleton.h>
#include <Wyvern/Renderer/cViewport.h>

#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class iLayer;
	
///////////////////////////////////////////////////////////////////////////////////////

	class cApplication : public iSingleton<cApplication>
	{

	public:

		void run( void );
		void pushLayer( iLayer* _layer ) { m_layerStack.push_back( _layer ); }
		
///////////////////////////////////////////////////////////////////////////////////////

		double       getTime     ( void ) { return m_time; }
		double       getDeltaTime( void ) { return m_deltaTime; }
		cSceneGraph& getScene    ( void ) { return m_sceneGraph; }
		cViewport&   getViewport ( void ) { return m_viewport; }

///////////////////////////////////////////////////////////////////////////////////////

		void startLoadThread();


///////////////////////////////////////////////////////////////////////////////////////

	private:

		int  create     ( void );
		void destroy    ( void );
		void initImgui  ( void ); // move
		void update     ( void );
		void draw       ( void );

///////////////////////////////////////////////////////////////////////////////////////

		cLayerStack m_layerStack;
		cSceneGraph m_sceneGraph;
		cViewport   m_viewport;

		double      m_lastTime  = 0.0;
		double      m_time      = 0.0;
		double      m_deltaTime = 0.0f;

	};

///////////////////////////////////////////////////////////////////////////////////////

}

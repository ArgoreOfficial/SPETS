#pragma once

#include <Wyvern/Core/iLayer.h>
#include <Wyvern/cApplication.h>

#include "cImportingWindow.h"

///////////////////////////////////////////////////////////////////////////////////////

namespace wv { class iCamera; }

///////////////////////////////////////////////////////////////////////////////////////

class GameLayer : public wv::iLayer
{

public:

	GameLayer( void ) :
		iLayer( "GameLayer" ), 
		m_scene( wv::cApplication::getInstance().getScene() )
	{
	};

	~GameLayer( void ) { };

///////////////////////////////////////////////////////////////////////////////////////

	void start ( void )              override;
	void update( double _deltaTime ) override;
	void draw3D( void )              override;
	void draw2D( void )              override { }
	void drawUI( void )              override;
	
///////////////////////////////////////////////////////////////////////////////////////

	wv::cSceneGraph& m_scene;
	wv::iCamera*     m_camera3D = nullptr;
	wv::iCamera*     m_camera2D = nullptr;

	cImportingWindow m_importingWindow;
};


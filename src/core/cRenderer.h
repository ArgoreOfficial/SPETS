#pragma once

#include "Engine.h"

class cWindow;

class cRenderer
{
public:
	cRenderer();
	~cRenderer();
	
	bool create( cWindow& _window );
	void destroy();

	void clear( unsigned char _color );

	void beginFrame();
	void endFrame();

private:

	void setupImGui( cWindow& _window );
	void shutdownImGui();

	void setupImGuiStyle();

};

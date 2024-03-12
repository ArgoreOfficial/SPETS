#pragma once

#include "cWindow.h"
#include "cRenderer.h"
#include <string>

#include <window/cHubWindow.h>

class cApplication
{

public:
	 cApplication();
	~cApplication();

	void start();
	void run();
	void shutdown();

	std::string getVersion();

private:

	struct sVersion
	{
		char type;
		int major;
		int minor;
		int year;
		int revision;
	};

	cWindow m_window;
	cRenderer m_renderer;

	cHubWindow m_hub_window;

	cApplication::sVersion m_version;
};
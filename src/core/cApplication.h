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

	static cApplication* getInstance()
	{
		static cApplication* instance = nullptr;
		if ( !instance )
			instance = new cApplication();

		return instance;
	}

	void checkScreenBounds( int _min_x, int _min_y, int _max_x, int _max_y, bool _hovering );

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

	cWindow m_window;
	cRenderer m_renderer;

	cHubWindow m_hub_window;

	cApplication::sVersion m_version;

	int m_min_x = 0;
	int m_min_y = 0;
	int m_max_x = 0;
	int m_max_y = 0;
	bool m_hovering = false;
};
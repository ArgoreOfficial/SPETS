#pragma once

#include "iWindow.h"
#include "cImportingWindow.h"

class cHubWindow : public iWindow
{
public:

	 cHubWindow( void );
	~cHubWindow( void );

	virtual void onCreate ( void ) override;
	virtual void onDestroy( void ) override;

protected:

	virtual void drawWindow() override;

private:

	cImportingWindow m_importing_window;

};
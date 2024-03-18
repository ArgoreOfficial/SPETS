#pragma once

#include "iWindow.h"
#include "tool/cImportingWindow.h"
#include "tool/cToolButton.h"

class cHubWindow : public iWindow
{
public:

	 cHubWindow( void );
	~cHubWindow( void );

	virtual void onCreate ( void ) override;
	virtual void onDestroy( void ) override;

private:

	virtual void drawWindow() override;


	cImportingWindow m_importing_window;

	cToolButton m_import_button;
	cToolButton m_export_button;
	cToolButton m_advanced_button;
	cToolButton m_edit_button;

};
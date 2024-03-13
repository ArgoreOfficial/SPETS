#pragma once

#include "iWindow.h"

#include <vector>
#include <string>

class cImportingWindow : public iWindow
{
public:
	 cImportingWindow();
	~cImportingWindow();

	virtual void onCreate ( void ) override;
	virtual void onDestroy( void ) override;

private:

	virtual void drawWindow() override;

	void getFactions();

private:

	std::vector<std::string> m_factions;
	std::string m_selected_faction;

};

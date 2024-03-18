#pragma once

#include "iToolWindow.h"

#include <vector>
#include <string>

class cImportingWindow : public iToolWindow
{
public:
	 cImportingWindow();
	~cImportingWindow();

	virtual void onCreate ( void ) override;
	virtual void onDestroy( void ) override;
	
private:

	virtual void drawWindow() override;

	void getFactions();
	void importMesh();

private:

	std::vector<std::string> m_factions;
	std::string m_selected_faction;

};

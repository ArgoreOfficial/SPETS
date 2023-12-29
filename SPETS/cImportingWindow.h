#pragma once

#include <string>
class cImportingWindow
{
public:
	cImportingWindow();
	~cImportingWindow();

	void drawUI();
	std::string openFile();
};
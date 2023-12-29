#include "cImportingWindow.h"
#include <imgui.h>
#include <windows.h>
#include <shobjidl.h> 
cImportingWindow::cImportingWindow()
{
}

cImportingWindow::~cImportingWindow()
{
}

void cImportingWindow::drawUI()
{
	if ( ImGui::BeginChild( "ImportingWindow" ) )
	{
		if ( ImGui::Button( "Load" ) )
		{
			printf( openFile().c_str() );

		}

	}
	ImGui::EndChild();	
}

std::string cImportingWindow::openFile()
{
	std::string out = "err: not implemented yet\n";

	return out;
}

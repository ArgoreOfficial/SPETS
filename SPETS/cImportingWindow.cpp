#include "cImportingWindow.h"
#include <imgui.h>

cImportingWindow::cImportingWindow()
{
}

cImportingWindow::~cImportingWindow()
{
}

void cImportingWindow::drawUI()
{
	ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID); // disable multi-viewport on this window
	if ( ImGui::Begin( "Import" ) )
	{

	}
	ImGui::End();
}

#include "cHubWindow.h"

#include <imgui.h>

cHubWindow::cHubWindow( void ):
	m_import_button  ( "Import",   &m_importing_window ),
	m_export_button  ( "Export",   &m_importing_window ),
	m_advanced_button( "Advanced", &m_importing_window ),
	m_edit_button    ( "Edit",     &m_importing_window )
{
	
}

cHubWindow::~cHubWindow( void )
{
	
}

void cHubWindow::onCreate( void )
{
	m_importing_window.onCreate();
}

void cHubWindow::onDestroy( void )
{
	m_importing_window.onDestroy();
}

void cHubWindow::drawWindow()
{
	if ( ImGui::Begin( "SPETS Tool Hub", &m_is_open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking ) )
	{
		if ( ImGui::BeginTabBar( "HUB_BAR" ) )
		{
			if ( ImGui::BeginTabItem( "Blueprints" ) )
			{
				m_import_button.draw();
				ImGui::SameLine();
				m_export_button.draw();
				ImGui::SameLine();
				m_advanced_button.draw();
				ImGui::SameLine();
				m_edit_button.draw();

				ImGui::EndTabItem();
			}
			
			if ( ImGui::BeginTabItem( "Modding" ) )
			{
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();

		update();
	}
	ImGui::End();

	m_importing_window.draw();
}

STDMETHODIMP_( HRESULT __stdcall ) cHubWindow::DragEnter( IDataObject* _pDataObj, DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect )
{
	return S_OK;
}

STDMETHODIMP_( HRESULT __stdcall ) cHubWindow::DragOver( DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect )
{

	return S_OK;
}

STDMETHODIMP_( HRESULT __stdcall ) cHubWindow::DragLeave()
{
	return S_OK;
}

STDMETHODIMP_( HRESULT __stdcall ) cHubWindow::Drop( IDataObject* _pDataObj, DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect )
{
	return S_OK;
}

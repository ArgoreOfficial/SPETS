#pragma once

#include "iWindow.h"
#include "tool/cImportingWindow.h"
#include "tool/cToolButton.h"

#include <oleidl.h>

class cHubWindow : public iWindow, public IDropTarget
{
public:

	 cHubWindow( void );
	~cHubWindow( void );

	virtual void onCreate ( void ) override;
	virtual void onDestroy( void ) override;
	
	STDMETHODIMP DragEnter( IDataObject* _pDataObj, DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect ) override;
	STDMETHODIMP DragOver ( DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect ) override;
	STDMETHODIMP DragLeave() override;
	STDMETHODIMP Drop     ( IDataObject* _pDataObj, DWORD _grfKeyState, POINTL _pt, DWORD* _pdwEffect ) override;


private:

	ULONG AddRef() override { return 0; }
	HRESULT QueryInterface( REFIID _riid, void** _object ) override { return S_OK; }
	ULONG Release() override { return 0; }

	virtual void drawWindow() override;


	cImportingWindow m_importing_window;

	cToolButton m_import_button;
	cToolButton m_export_button;
	cToolButton m_advanced_button;
	cToolButton m_edit_button;

};
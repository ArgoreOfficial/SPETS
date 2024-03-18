#pragma once

#include <oleidl.h>
#include <shellapi.h>

#include <vector>
#include <string>

class cDragDropSurface : public IDropTarget
{
public:

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppvObject ) { return S_OK; }
	virtual ULONG   STDMETHODCALLTYPE AddRef        ( void )                          { return 0; }
	virtual ULONG   STDMETHODCALLTYPE Release       ( void )                          { return 0; }

	virtual HRESULT STDMETHODCALLTYPE DragEnter( IDataObject* _data_object, DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect ) override;
	virtual HRESULT STDMETHODCALLTYPE DragOver ( DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect ) override;
	virtual HRESULT STDMETHODCALLTYPE DragLeave( void ) override;
	virtual HRESULT STDMETHODCALLTYPE Drop     ( IDataObject* _data_object, DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect ) override;

	std::vector<std::string>& getDroppedPaths( void ) { return m_drop_paths; }
	bool isDraggingFile( void ) { return m_dragging; }

private:

	bool m_dragging = false;
	
	std::vector<std::string> m_drop_paths;
};
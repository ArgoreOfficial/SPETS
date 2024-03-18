#include "cDragDropSurface.h"

#include <locale>
#include <codecvt>
#include <atlstr.h>

HRESULT __stdcall cDragDropSurface::DragEnter( IDataObject* _data_object, DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect )
{
	if ( _drop_effect == NULL )
		return E_INVALIDARG;

	*_drop_effect |= DROPEFFECT_COPY;

	m_dragging = true;
	return S_OK;
}

HRESULT __stdcall cDragDropSurface::DragOver( DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect )
{
	if ( _drop_effect == NULL )
		return E_INVALIDARG;

	*_drop_effect |= DROPEFFECT_COPY;

	return S_OK;
}

HRESULT __stdcall cDragDropSurface::DragLeave( void )
{
	m_dragging = false; 
	return S_OK;
}

HRESULT __stdcall cDragDropSurface::Drop( IDataObject* _data_object, DWORD _keyboard_state, POINTL _mouse_pos, DWORD* _drop_effect )
{
	if ( _drop_effect == NULL )
		return E_INVALIDARG;

	*_drop_effect |= DROPEFFECT_COPY;

	FORMATETC format;
	STGMEDIUM medium;
	format.cfFormat = CF_HDROP;
	format.ptd = NULL;
	format.dwAspect = DVASPECT_CONTENT;
	format.lindex = -1;
	format.tymed = TYMED_HGLOBAL;
	medium.tymed = TYMED_HGLOBAL;
	HRESULT res = _data_object->GetData( &format, &medium );
	HDROP drop = (HDROP)medium.hGlobal;
	wchar_t* filename = nullptr;
	//See https://docs.microsoft.com/en-us/windows/desktop/api/shellapi/nf-shellapi-dragqueryfilew
	UINT filePathesCount = DragQueryFile( drop, 0xFFFFFFFF, NULL, 512 );//If "0xFFFFFFFF" as the second parameter: return the count of files dropped
	UINT longest_filename_length = 0;

	for ( UINT i = 0; i < filePathesCount; ++i )
	{
		//If NULL as the third parameter: return the length of the path, not counting the trailing '0'
		UINT filename_length = DragQueryFile( drop, i, NULL, 512 ) + 1;
		if ( filename_length > longest_filename_length )
		{
			if ( filename )
			{
				delete[] filename;
				filename = nullptr;
			}
			
			longest_filename_length = filename_length;
			filename = new wchar_t[ longest_filename_length * sizeof( *filename ) ];
		}
		DragQueryFile( drop, i, filename, filename_length );

		m_drop_paths.push_back( std::string( CW2A( filename ) ) );
	}
	if ( filename )
	{
		delete[] filename;
		filename = nullptr;
	}

	ReleaseStgMedium( &medium );
	m_dragging = false; 

	return S_OK;
}

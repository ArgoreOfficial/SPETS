#include "Util.h"

#include <Windows.h>
#include <shlobj.h>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Ole32.lib")

std::filesystem::path SPETS::getFolderPath( const KNOWNFOLDERID& _id )
{
	wchar_t* wpath = nullptr;
	if ( SHGetKnownFolderPath( _id, 0, NULL, &wpath ) != S_OK )
	{
		CoTaskMemFree( static_cast<void*>( wpath ) );
		return "";
	}

	std::wstringstream stream;
	stream << wpath;

	std::filesystem::path path = wpath;
	CoTaskMemFree( static_cast<void*>( wpath ) );

	return path;
}

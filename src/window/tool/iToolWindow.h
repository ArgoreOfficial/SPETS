#pragma once

#include "../iWindow.h"
#include <string>

#include <atlstr.h>

class iToolWindow : public iWindow
{
	SPETS_INTERFACE( iToolWindow )

public:
	virtual void loadFile( std::string _path )
	{
		m_file_path = _path.c_str();
		m_filename  = _path.substr( _path.find_last_of( "/\\" ) + 1 ).c_str();
	}

protected:

	std::string m_file_path;
	std::string m_filename;

};

#pragma once

#include "../iWindow.h"
#include <string>

class iToolWindow : public iWindow
{
	SPETS_INTERFACE( iToolWindow )

public:
	virtual void loadFile( std::string _path )
	{
		m_file_path = _path;
	}

protected:

	std::string m_file_path;

};

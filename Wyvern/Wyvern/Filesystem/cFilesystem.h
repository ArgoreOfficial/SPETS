#pragma once

#include <string>
#include <vector>

                          /////////////////////////////
                          /// A lot of rework needed //
                          /////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

	namespace Filesystem
	{

///////////////////////////////////////////////////////////////////////////////////////

		bool                fileExists           ( std::string _path, bool _printError = false );
		std::string         getFilenameFromPath  ( std::string _path, bool _keepExtension = true );
		std::string         getFileExtension     ( std::string _path );
		std::vector<char>   loadByteArrayFromPath( std::string _path );
		std::string         loadFileToString     ( std::string _path );

///////////////////////////////////////////////////////////////////////////////////////

	}

}
#include <iostream>

#include <tools/importer/cMeshImporter.h>

#include "core/cApplication.h"

int main( int argc, char* argv[] )
{
#ifdef FINAL
	ShowWindow( GetConsoleWindow(), SW_HIDE );
#endif

	cApplication& app = *cApplication::getInstance();;
	app.start();
	app.run();
	app.shutdown();
	
	return 0;
}


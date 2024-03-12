#include <iostream>

#include <tools/importer/cMeshImporter.h>

#include "core/cApplication.h"

int main( int argc, char* argv[] )
{
	cApplication app;
	app.start();
	app.run();
	app.shutdown();
	/*
	std::string path = "../res/cubes.glb";

	if ( argc > 1 )
		path = argv[ 1 ];

	cMeshImporter importer( path );
	*/

	return 0;
}


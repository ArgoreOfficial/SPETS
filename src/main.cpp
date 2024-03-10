#include <iostream>

#include <tools/importer/cMeshImporter.h>

int main( int argc, char* argv[] )
{
	std::string path = "../res/cubes.glb";

	if ( argc > 1 )
		path = argv[ 1 ];

	cMeshImporter importer( path );

	return 0;
}


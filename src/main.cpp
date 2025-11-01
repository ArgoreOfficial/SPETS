#include <stdio.h>
#include "Sprocket/Sprocket.h"

int main()
{
	Sprocket::MeshData importedMesh;
	if ( Sprocket::importMesh( "../models/teapot.glb", importedMesh ) )
	{
		importedMesh.name = "Teapot";

		// scale and move the vertices
		for ( size_t i = 0; i < importedMesh.mesh.getNumVertices(); i++ )
		{
			importedMesh.mesh.scaleVertexPosition( i, 0.5f, 0.5f, 0.5f );
			importedMesh.mesh.moveVertexPosition( i, 0.0f, -0.5f, 0.0f );
		}

		Sprocket::saveCompartmentToFile( "teapot.blueprint", importedMesh );
	}
	
	return 0;
}

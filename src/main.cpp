#include <stdio.h>
#include "Sprocket/Sprocket.h"

int main()
{
	Sprocket::MeshData compartment;
	if ( Sprocket::loadCompartmentFromFile( "../blueprints/Plate Structures/Turret.blueprint", compartment ) )
	{
		printf( "Loaded compartment \"%s\"\n", compartment.name.c_str() );
		
		for ( size_t i = 0; i < compartment.mesh.getNumVertices(); i++ )
			compartment.mesh.moveVertexPosition( i, 0.0f, 1.0f, 0.0f );
		
		compartment.name = "Turret2";

		Sprocket::saveCompartmentToFile( "Turret2.blueprint", compartment );
	}
	
	return 0;
}

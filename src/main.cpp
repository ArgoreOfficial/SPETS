#include <stdio.h>
#include "Sprocket/Sprocket.h"

int main()
{
	Sprocket::MeshData compartment;
	if ( Sprocket::loadCompartmentFromFile( "../blueprints/Plate Structures/Turret.blueprint", compartment ) )
	{
		printf( "Loaded compartment \"%s\"\n", compartment.name.c_str() );
		// do stuff with compartment
	}
	
	return 0;
}

#include <stdio.h>

#include "SPETS/ArgParser.h"
#include "Sprocket/Sprocket.h"

int main( int _argc, char* _argv[] )
{
	SPETS::ArgParser parser{};

	std::vector<char*> argv = { 
		_argv[ 0 ],
		(char*)"-f", (char*)"DEV",
		(char*)"-i", (char*)"..\\models\\teapot.glb",
		(char*)"-o", (char*)"Teapot"
	};

	parser.addArg( "-f" )
		.setType( SPETS::ArgType_String )
		.setDefault( "Default" );

	parser.addArg( "-i" )
		.setType( SPETS::ArgType_String );

	parser.addArg( "-o" )
		.setType( SPETS::ArgType_String )
		.setDefault( "Import" );

	bool parsed = false;
	
	if( _argc == 1 )
		parsed = parser.parseArguments( argv.size(), argv.data() );
	else
		parsed = parser.parseArguments( _argc, _argv );

	if ( parsed )
	{
		SPETS::ArgInfo& factionInfo = parser.get( "-f" );
		SPETS::ArgInfo& inputInfo   = parser.get( "-i" );
		SPETS::ArgInfo& outputInfo  = parser.get( "-o" );

		std::string faction = factionInfo.getValue<std::string>();
		std::string input   = inputInfo.getValue<std::string>();;
		std::string output  = outputInfo.getValue<std::string>();;

		if ( !factionInfo.isSet() ) printf( "No faction specified. File will be placed in 'Default'.\n" );
		if ( !outputInfo .isSet() ) printf( "No output file specified. Defaulting to 'Import.blueprint'\n" );
		
		if ( !inputInfo  .isSet() ) 
			printf( "No file input file specified. Use -i <file>\n" );
		else if ( !Sprocket::doesFactionExist( faction ) )
			printf( "Faction %s does not exist.\n", faction.c_str() );
		else
		{
			printf( "Importing... " );

			std::string factionPath = Sprocket::getFactionPath( faction );
			std::string exportPath = factionPath + "Blueprints\\Plate Structures\\" + output + ".blueprint";
			Sprocket::MeshData importedMesh;

			if ( Sprocket::importMesh( input, importedMesh ) )
			{
				importedMesh.name = output;
				Sprocket::saveCompartmentToFile( 
					exportPath, 
					importedMesh 
				);
				
				printf( "DONE\n" );
			}
			else
				printf( "ERROR :(\n" );
		}
	}
	else
	{
		printf( "Error: %s\n", parser.getErrorMessage().c_str() );
	}

	return 0;
}

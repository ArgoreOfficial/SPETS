#include <stdio.h>

#include "SPETS/ArgParser.h"
#include "Sprocket/Sprocket.h"

SPETS::ArgParser createParser()
{
	SPETS::ArgParser parser{};

	parser.addArg( "-f" )
		.setInputName( "faction" )
		.setDesc( "Target faction" )
		.setType( SPETS::ArgType_String )
		.setDefault( "Default" );

	parser.addArg( "-i" )
		.setInputName( "file" )
		.setDesc( "Input file" )
		.setType( SPETS::ArgType_String );

	parser.addArg( "-o" )
		.setInputName( "name" )
		.setDesc( "Output blueprint name" )
		.setType( SPETS::ArgType_String )
		.setDefault( "Import" );

	parser.addArg( "--help" )
		.setDesc( "Display this help page" )
		.setType( SPETS::ArgType_Flag )
		.setDefault( false )
		.setImplicit( true );

	return parser;
}

int main( int _argc, char* _argv[] )
{
	Sprocket::FactionInfo defaultInfo = Sprocket::getFactionInfo( "Default" );

	SPETS::ArgParser parser = createParser();
	bool parsed = false;

	// debug build test stuff
	std::vector<char*> argv = { 
		_argv[ 0 ],
		(char*)"-f", (char*)"DEV",
		(char*)"-i", (char*)"..\\models\\teapot.glb",
		(char*)"-o", (char*)"Teapot"
	};

	if( _argc == 1 )
		parsed = parser.parseArguments( argv.size(), argv.data() );
	else
		parsed = parser.parseArguments( _argc, _argv );

	if ( parsed )
	{
		if ( parser.get( "--help" ) == true )
		{
			parser.printHelp();
			return 0;
		}

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

			std::filesystem::path factionPath = Sprocket::getFactionPath( faction );
			std::filesystem::path exportPath = factionPath / "Blueprints" / "Plate Structures" / output / ".blueprint";
			Sprocket::MeshData importedMesh;

			if ( Sprocket::importMesh( input, importedMesh ) )
			{
				importedMesh.name = output;
				Sprocket::saveCompartmentToFile( 
					exportPath.string(),
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


#include <SPETS/ArgParser.h>
#include <SPETS/GUI/ApplicationHub.h>
#include <Sprocket/Sprocket.h>

#include <fstream>
#include <stdio.h>

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

void runCommandLine( int _argc, char* _argv[] )
{
	SPETS::ArgParser parser = createParser();

	if ( !parser.parseArguments( _argc, _argv ) )
	{
		printf( "Error: %s\n", parser.getErrorMessage().c_str() );
		return;
	}

	if ( parser.get( "--help" ) == true )
	{
		parser.printHelp();
		return;
	}

	SPETS::ArgInfo& factionInfo = parser.get( "-f" );
	SPETS::ArgInfo& inputInfo = parser.get( "-i" );
	SPETS::ArgInfo& outputInfo = parser.get( "-o" );

	std::string faction = factionInfo.getValue<std::string>();
	std::string input   = inputInfo.getValue<std::string>();;
	std::string output  = outputInfo.getValue<std::string>();;

	if ( !factionInfo.isSet() ) printf( "No faction specified. File will be placed in 'Default'.\n" );
	if ( !outputInfo.isSet() ) printf( "No output file specified. Defaulting to 'Import.blueprint'\n" );

	if ( !inputInfo.isSet() )
		printf( "No file input file specified. Use -i <file>\n" );
	else if ( !Sprocket::doesFactionExist( faction ) )
		printf( "Faction %s does not exist.\n", faction.c_str() );
	else
	{
		printf( "Importing %s... ", output.c_str() );

		Sprocket::MeshData importedMesh;
		if ( Sprocket::createCompartmentFromMesh( input, importedMesh ) )
		{
			importedMesh.name = output;
			Sprocket::saveCompartmentToFaction( importedMesh, faction, output );
			printf( "DONE\n" );
		}
		else
			printf( "ERROR :(\n" );
	}
}

int main( int _argc, char* _argv[] )
{
	std::string currentFaction = Sprocket::getCurrentFaction();
	Sprocket::FactionInfo factionInfo = Sprocket::getFactionInfo( currentFaction );

	printf( "================ SPETS ================\n" );

	printf( "Current faction is %s\n", factionInfo.name.c_str() );
	printf( "Prefix: '%s' (%s123)\n", factionInfo.designPrefix.c_str(), factionInfo.designPrefix.c_str() );
	printf( "Design Count: %d\n", factionInfo.designCounter );
	
	printf( "=======================================\n" );

	if ( _argc > 1 )
		runCommandLine( _argc, _argv ); // run through command line
	else
	{
	#ifndef NDEBUG
		std::vector<char*> argv = { _argv[0],
			(char*)"-f", (char*)"DEV",
			(char*)"-i", (char*)"../models/cube.dae",
			(char*)"-o", (char*)"Cube"
		};

		runCommandLine(argv.size(), argv.data());
	#endif

		wxEntry( _argc, _argv );
	}

	return 0;
}

wxIMPLEMENT_APP_NO_MAIN( SPETS::Application );

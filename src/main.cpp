#include <stdio.h>

#include <SPETS/ArgParser.h>
#include <Sprocket/Sprocket.h>

#include <fstream>

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
		printf( "Importing... " );

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
	if ( _argc > 1 )
		runCommandLine( _argc, _argv );
#ifndef NDEBUG 
	else
	{
		std::vector<char*> argv = { _argv[0],
			(char*)"-f", (char*)"DEV",
			(char*)"-i", (char*)"../models/cube.dae",
			(char*)"-o", (char*)"Cube"
		};

		runCommandLine(argv.size(), argv.data());
		
		std::string currentFaction = Sprocket::getCurrentFaction();
		Sprocket::FactionInfo factionInfo = Sprocket::getFactionInfo( currentFaction );
		Sprocket::CustomBattleConfig cbi = Sprocket::getCustomBattleSetup();
		Sprocket::saveCustomBattleSetup( cbi );

		Sprocket::VehicleBlueprint bratten;
		if ( Sprocket::loadBlueprint( "Default", "B4 Bratten", bratten ) )
			Sprocket::exportBlueprintToFile( bratten );
		
		Sprocket::MeshData bofors;
		if ( Sprocket::loadBlueprintFromFile( "bofors shells.blueprint", bofors ) )
			Sprocket::exportBlueprintToFile( bofors, "bofors" );
		
	}
#endif

	return 0;
}

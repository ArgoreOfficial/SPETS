#define NOMINMAX

#include "CustomBattle.h"

#include <Sprocket/Sprocket.h>
#include <Sprocket/Json.h>
#include <SPETS/Util.h>

#include <fstream>

void Sprocket::TeamDefinition::addUnits( int _count, const std::string& _path )
{
	// if the file doesn't exist, Sprocket will delete the CustomBattleSetup.json file. Not good!
	if ( _path == "" || !std::filesystem::exists( _path ) )
		return;

	UnitInstanceInfo instance{ std::max(0, _count ) };
	UnitDefinition def{ _path, "" };
	
	units.push_back( { instance, def } );
}

void Sprocket::TeamDefinition::addUnits( int _count, const std::string& _faction, const std::string& _vehicleName )
{
	if ( !Sprocket::doesBlueprintExist( _faction, _vehicleName ) )
		return;

	std::filesystem::path bpPath = Sprocket::getBlueprintPath( _faction, _vehicleName );
	addUnits( _count, bpPath.string() );
}

Sprocket::CustomBattleConfig Sprocket::getCustomBattleSetup()
{
	std::filesystem::path appdata = SPETS::getFolderPath( FOLDERID_LocalAppDataLow );
	std::filesystem::path path = appdata / "HD" / "Sprocket" / "CustomBattleSetup.json";

	std::ifstream f( path );
	if ( !f )
		return {};

	nlohmann::json json = nlohmann::json::parse( f );
	return json.get<Sprocket::CustomBattleConfig>();
}

void Sprocket::saveCustomBattleSetup( const CustomBattleConfig& _info )
{
	std::filesystem::path appdata = SPETS::getFolderPath( FOLDERID_LocalAppDataLow );
	std::filesystem::path path = appdata / "HD" / "Sprocket" / "CustomBattleSetup.json";

	std::ofstream f( path );
	if ( !f )
		return;

	nlohmann::json json = _info;
	f << json.dump();
}

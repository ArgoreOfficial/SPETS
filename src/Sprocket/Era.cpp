#include "Era.h"

#include <Sprocket/Sprocket.h>
#include <Sprocket/Json.h>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

std::vector<Sprocket::EraDefinition> Sprocket::getAllEras()
{
	std::filesystem::path sa = Sprocket::getStreamingAssetsPath() / "Eras";
	if ( !std::filesystem::exists( sa ) )
		return {};

	std::vector<Sprocket::EraDefinition> defs;

	for ( const auto& entry : std::filesystem::directory_iterator( sa ) )
	{
		if ( entry.is_directory() )
			continue;

		std::ifstream f( entry.path() );
		if ( !f )
			continue;

		nlohmann::json json = nlohmann::json::parse( f );
		Sprocket::EraDefinition era = json.get<Sprocket::EraDefinition>();
		
		defs.push_back( era );
	}
	
	return defs;
}

Sprocket::EraDefinition Sprocket::getEra( const std::string& _name )
{
	return {};
}

void Sprocket::saveEra( const EraDefinition& _era )
{
	std::filesystem::path sa = Sprocket::getStreamingAssetsPath() / "Eras";
	
	std::ofstream f( sa / ( _era.name + ".json" ) );
	if ( !f )
		return;

	nlohmann::json j = _era;
	f << j.dump();
}

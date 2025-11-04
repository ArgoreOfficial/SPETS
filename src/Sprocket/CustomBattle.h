#pragma once

#include <string>
#include <vector>

namespace Sprocket {

struct EnvironmentConfig
{
	float timeCycleFraction = 0.175; // seemingly doesn't do anything 

	// all 0.0 = Clear
	float cloudy     = 0.0f;
	float overcast   = 0.0f;
	float highClouds = 1.0f;
	float unk        = 0.0f; // unused?

	float fogDistance = 250.0f;

	void setCloudsClear     ( void ) { cloudy = 0.0f; overcast = 0.0f; highClouds = 0.0f; unk = 0.0f; }
	void setCloudsCloudy    ( void ) { cloudy = 1.0f; overcast = 0.0f; highClouds = 0.0f; unk = 0.0f; }
	void setCloudsOvercast  ( void ) { cloudy = 0.0f; overcast = 1.0f; highClouds = 0.0f; unk = 0.0f; }
	void setCloudsHighClouds( void ) { cloudy = 0.0f; overcast = 0.0f; highClouds = 1.0f; unk = 0.0f; }

	void setFogNone     ( void ) { fogDistance = 1000.0f; }
	void setFogLight    ( void ) { fogDistance = 500.0f; }
	void setFogMedium   ( void ) { fogDistance = 250.0f; }
	void setFogHeavy    ( void ) { fogDistance = 100.0f; }
	void setFogVeryHeavy( void ) { fogDistance = 20.0f; }
};

struct UnitDefinition
{
	std::string path;
	std::string iconPath;
};

struct UnitInstanceInfo
{
	int count;
};

enum TeamDefinitionFlags
{
	TeamDefinitionFlags_None          = 0x0,
	TeamDefinitionFlags_Player        = 0x1,
	TeamDefinitionFlags_Attacker      = 0x2,
	TeamDefinitionFlags_Defender      = 0x4,
	TeamDefinitionFlags_RequiresUnits = 0x8
};

struct TeamDefinition
{
	std::vector<std::pair<UnitInstanceInfo, UnitDefinition>> units;
	TeamDefinitionFlags flags = TeamDefinitionFlags_None;
	std::string paint;
	float condition = 1.0;
	float dirt = 0.1;
	int budget = 250000;

	void setBudgetVeryLow  ( void ) { budget = 12000; }
	void setBudgetLow      ( void ) { budget = 40000; }
	void setBudgetMedium   ( void ) { budget = 75000; }
	void setBudgetHigh     ( void ) { budget = 125000; }
	void setBudgetVeryHigh ( void ) { budget = 250000; }
	void setBudgetUnlimited( void ) { budget = -1; }

	int  getUnitCount( size_t _index             ) const { return units[ _index ].first.count; }
	void setUnitCount( size_t _index, int _count )       { units[ _index ].first.count = std::max(0, _count); }

	UnitDefinition getUnitDef( size_t _index                              ) const { return units[ _index ].second; }
	void           setUnitDef( size_t _index, const UnitDefinition& _unit )       { units[ _index ].second = _unit; }

	void addUnits( int _count, const std::string& _path );
	void addUnits( int _count, const std::string& _faction, const std::string& _vehicleName );
};

struct CustomBattleConfig
{
	std::string mapName;

	EnvironmentConfig environment;
	std::vector<TeamDefinition> teams;
};

CustomBattleConfig getCustomBattleSetup();
void saveCustomBattleSetup( const CustomBattleConfig& _info );

}
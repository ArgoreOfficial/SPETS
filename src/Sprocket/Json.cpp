#include "Json.h"

#include <nlohmann/json.hpp>

#define NULLCHECK(_key, _val) if ( !_json.at( _key ).is_null() ) { _json.at( _key ).get_to( _val ); }

void Sprocket::to_json( nlohmann::json& _json, const Sprocket::RivetTypeProfile& _p )
{
	_json = nlohmann::json{
		{ "model",    _p.model },
		{ "spacing",  _p.spacing },
		{ "diameter", _p.diameter },
		{ "height",   _p.height },
		{ "padding",  _p.padding }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::RivetTypeProfile& _p )
{
	_json.at( "model" ).get_to( _p.model );
	_json.at( "spacing" ).get_to( _p.spacing );
	_json.at( "diameter" ).get_to( _p.diameter );
	_json.at( "height" ).get_to( _p.height );
	_json.at( "padding" ).get_to( _p.padding );
}

// RivetNode
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::RivetNode& _p )
{
	_json = nlohmann::json{
		{ "next",       _p.next },
		{ "prev",       _p.prev },
		{ "face",       _p.face },
		{ "u",          _p.v },
		{ "v",          _p.v },
		{ "w",          _p.w },
		{ "faceOffset", _p.faceOffset },
		{ "profile",    _p.profile },
		{ "flags",      _p.flags }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::RivetNode& _p )
{
	_json.at( "next" ).get_to( _p.next );
	_json.at( "prev" ).get_to( _p.prev );
	_json.at( "face" ).get_to( _p.face );
	_json.at( "u" ).get_to( _p.u );
	_json.at( "v" ).get_to( _p.v );
	_json.at( "w" ).get_to( _p.w );
	_json.at( "faceOffset" ).get_to( _p.faceOffset );
	_json.at( "profile" ).get_to( _p.profile );
	_json.at( "flags" ).get_to( _p.flags );
}

// Rivets
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::Rivets& _p )
{
	_json = nlohmann::json{
		{ "profiles", _p.profiles },
		{ "nodes",    _p.nodes }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::Rivets& _p )
{
	_json.at( "profiles" ).get_to( _p.profiles );
	_json.at( "nodes" ).get_to( _p.nodes );
}

// SerializedFace
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::SerializedFace& _p )
{
	_json = nlohmann::json{
		{ "v",  _p.vertices },
		{ "t",  _p.thicknesses },
		{ "tm", _p.thickenModes.u32 },
		{ "te", _p.thickenEdgeIndicies.u64 }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::SerializedFace& _p )
{
	_json.at( "v" ).get_to( _p.vertices );
	_json.at( "t" ).get_to( _p.thicknesses );
	_json.at( "tm" ).get_to( _p.thickenModes.u32 );
	_json.at( "te" ).get_to( _p.thickenEdgeIndicies.u64 );
}

// MeshBlueprint
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::MeshBlueprint& _p )
{
	_json = nlohmann::json{
		{ "majorVersion", _p.majorVersion },
		{ "minorVersion", _p.minorVersion },
		{ "vertices",     _p.vertexPositions },
		{ "edges",        _p.serializedEdges },
		{ "edgeFlags",    _p.serializedEdgeFlags },
		{ "faces",        _p.serializedFaces }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::MeshBlueprint& _p )
{
	_json.at( "majorVersion" ).get_to( _p.majorVersion );
	_json.at( "minorVersion" ).get_to( _p.minorVersion );
	_json.at( "vertices" ).get_to( _p.vertexPositions );
	_json.at( "edges" ).get_to( _p.serializedEdges );
	_json.at( "edgeFlags" ).get_to( _p.serializedEdgeFlags );
	_json.at( "faces" ).get_to( _p.serializedFaces );
}

// MeshData
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::MeshData& _p )
{
	_json = nlohmann::json{
		{ "v",           _p.version },
		{ "name",        _p.name },
		{ "smoothAngle", _p.smoothAngle },
		{ "gridSize",    _p.gridSize },
		{ "format",      _p.format },
		{ "mesh",        _p.mesh },
		{ "rivets",      _p.rivets }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::MeshData& _p )
{
	_json.at( "v" ).get_to( _p.version );
	NULLCHECK( "name", _p.name );
	_json.at( "smoothAngle" ).get_to( _p.smoothAngle );
	_json.at( "gridSize" ).get_to( _p.gridSize );
	_json.at( "format" ).get_to( _p.format );
	_json.at( "mesh" ).get_to( _p.mesh );
	_json.at( "rivets" ).get_to( _p.rivets );

}

// SerializableMesh
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::SerializableMesh& _p )
{
	_json = nlohmann::json{
		{ "vuid",     _p.vuid },
		{ "type",     _p.type },
		{ "meshData", _p.meshData }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::SerializableMesh& _p )
{
	_json.at( "vuid" ).get_to( _p.vuid );
	_json.at( "type" ).get_to( _p.type );
	_json.at( "meshData" ).get_to( _p.meshData );
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::VehicleBlueprintHeader& _p )
{
	_json.at( "v" ).get_to( _p.version );
	_json.at( "name" ).get_to( _p.name );
	_json.at( "gameVersion" ).get_to( _p.gameVersion );
	_json.at( "creationDate" ).get_to( _p.creationDate );
	_json.at( "mass" ).get_to( _p.mass );
	_json.at( "class" ).get_to( _p.classification );
	_json.at( "desc" ).get_to( _p.description );
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::VehicleBlueprint& _p )
{
	_json.at( "v" ).get_to( _p.version );
	_json.at( "header" ).get_to( _p.header );
	//_json.at( "blueprints" ).get_to( _p.blueprints );
	_json.at( "meshes" ).get_to( _p.meshes );
}

// EnvironmentConfig
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::EnvironmentConfig& _p )
{
	_json = nlohmann::json{
		{ "TimeCycleFraction", _p.timeCycleFraction },
		{ "CloudMapR",         _p.cloudy },
		{ "CloudMapG",         _p.overcast },
		{ "CloudMapB",         _p.highClouds },
		{ "CloudMapA",         _p.unk },
		{ "FogDistance",       _p.fogDistance }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::EnvironmentConfig& _p )
{
	_json.at( "TimeCycleFraction" ).get_to( _p.timeCycleFraction );
	_json.at( "CloudMapR" ).get_to( _p.cloudy );
	_json.at( "CloudMapG" ).get_to( _p.overcast );
	_json.at( "CloudMapB" ).get_to( _p.highClouds );
	_json.at( "CloudMapA" ).get_to( _p.unk );
	_json.at( "FogDistance" ).get_to( _p.fogDistance );
}

// UnitDefinition
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::UnitDefinition& _p )
{
	_json = nlohmann::json{
		   { "path", _p.path },
		   { "iconPath", _p.iconPath }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::UnitDefinition& _p )
{
	_json.at( "path" ).get_to( _p.path );
	_json.at( "iconPath" ).get_to( _p.iconPath );
}

// UnitInstanceInfo
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::UnitInstanceInfo& _p )
{
	_json = nlohmann::json{
		{ "Count", _p.count }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::UnitInstanceInfo& _p )
{
	_json.at( "Count" ).get_to( _p.count );
}

// TeamDefinition
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::TeamDefinition& _p )
{
	std::vector<int> budget{ _p.budget };
	std::vector<Sprocket::UnitDefinition> units;
	std::vector<Sprocket::UnitInstanceInfo> instances;

	for ( size_t i = 0; i < _p.units.size(); i++ )
	{
		instances.push_back( _p.units[ i ].first );
		units.push_back( _p.units[ i ].second );
	}

	_json = {
		{ "unitDefs",      units },
		{ "unitInstances", instances },
		{ "flags",         _p.flags },
		{ "paint",         _p.paint },
		{ "condition",     _p.condition },
		{ "dirt",          _p.dirt },
		{ "budget",        budget }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::TeamDefinition& _p )
{
	_json.at( "flags" ).get_to( _p.flags );
	_json.at( "paint" ).get_to( _p.paint );
	_json.at( "condition" ).get_to( _p.condition );
	_json.at( "dirt" ).get_to( _p.dirt );

	std::vector<int> budgets;
	_json.at( "budget" ).get_to( budgets );
	if ( budgets.size() > 0 ) _p.budget = budgets[ 0 ];
	else _p.budget = 250000;

	std::vector<Sprocket::UnitDefinition> units;
	_json.at( "unitDefs" ).get_to( units );

	std::vector<Sprocket::UnitInstanceInfo> instances;
	_json.at( "unitInstances" ).get_to( instances );

	size_t count = std::min( units.size(), instances.size() );
	for ( size_t i = 0; i < count; i++ )
		_p.units.push_back( { instances[ i ], units[ i ] } );
}

// CustomBattleInfo
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::CustomBattleConfig& _p )
{
	_json = nlohmann::json{
		{ "MapName",     _p.mapName },
		{ "Environment", _p.environment },
		{ "Teams",       _p.teams }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::CustomBattleConfig& _p )
{
	_json.at( "MapName" ).get_to( _p.mapName );
	_json.at( "Environment" ).get_to( _p.environment );
	_json.at( "Teams" ).get_to( _p.teams );
}

// EraDefinition
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::EraDefinition& _p )
{
	_json = nlohmann::json{
		{ "v",                 _p.v },
		{ "name",              _p.name },
		{ "start",             _p.start },
		{ "playable",          _p.playable },
		{ "mediumVehicleMass", _p.mediumVehicleMass },
		{ "heavyVehicleMass",  _p.heavyVehicleMass }
	};
}

void Sprocket::from_json( const nlohmann::json& _json, Sprocket::EraDefinition& _p )
{
	_json.at( "v" ).get_to( _p.v );
	_json.at( "name" ).get_to( _p.name );
	_json.at( "start" ).get_to( _p.start );
	_json.at( "playable" ).get_to( _p.playable );
	_json.at( "mediumVehicleMass" ).get_to( _p.mediumVehicleMass );
	_json.at( "heavyVehicleMass" ).get_to( _p.heavyVehicleMass );
}

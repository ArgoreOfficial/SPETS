#include "Json.h"

#include <nlohmann/json.hpp>

// RivetTypeProfile
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

// Rivets
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::Rivets& _p )
{
	_json = nlohmann::json{
		{ "profiles", _p.profiles },
		{ "nodes",    _p.nodes }
	};
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

// _plateStructureMesh
void Sprocket::to_json( nlohmann::json& _json, const Sprocket::PlateStructureMesh& _p )
{
	_json = nlohmann::json{
		{ "vuid",     _p.vuid },
		{ "type",     _p.type },
		{ "meshData", _p.meshData }
	};
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

// RivetTypeProfile
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::RivetTypeProfile& _p )
{
	_json.at( "model" ).get_to( _p.model );
	_json.at( "spacing" ).get_to( _p.spacing );
	_json.at( "diameter" ).get_to( _p.diameter );
	_json.at( "height" ).get_to( _p.height );
	_json.at( "padding" ).get_to( _p.padding );
}

// RivetNode
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
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::Rivets& _p )
{
	_json.at( "profiles" ).get_to( _p.profiles );
	_json.at( "nodes" ).get_to( _p.nodes );
}

// SerializedFace
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::SerializedFace& _p )
{
	_json.at( "v" ).get_to( _p.vertices );
	_json.at( "t" ).get_to( _p.thicknesses );
	_json.at( "tm" ).get_to( _p.thickenModes.u32 );
	_json.at( "te" ).get_to( _p.thickenEdgeIndicies.u64 );
}

// MeshBlueprint
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
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::MeshData& _p )
{
	_json.at( "v" ).get_to( _p.version );
	_json.at( "name" ).get_to( _p.name );
	_json.at( "smoothAngle" ).get_to( _p.smoothAngle );
	_json.at( "gridSize" ).get_to( _p.gridSize );
	_json.at( "format" ).get_to( _p.format );
	_json.at( "mesh" ).get_to( _p.mesh );
	_json.at( "rivets" ).get_to( _p.rivets );
}

// _plateStructureMesh
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::PlateStructureMesh& _p )
{
	_json.at( "vuid" ).get_to( _p.vuid );
	_json.at( "type" ).get_to( _p.type );
	_json.at( "meshData" ).get_to( _p.meshData );
}

// EraDefinition
void Sprocket::from_json( const nlohmann::json& _json, Sprocket::EraDefinition& _p )
{
	_json.at( "v" ).get_to( _p.v );
	_json.at( "name" ).get_to( _p.name );
	_json.at( "start" ).get_to( _p.start );
	_json.at( "playable" ).get_to( _p.playable );
	_json.at( "mediumVehicleMass" ).get_to( _p.mediumVehicleMass );
	_json.at( "heavyVehicleMass" ).get_to( _p.heavyVehicleMass );
}

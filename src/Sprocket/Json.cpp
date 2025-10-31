#include "Json.h"

#include <nlohmann/json.hpp>

// RivetTypeProfile
void Sprocket::to_json( nlohmann::json& j, const Sprocket::RivetTypeProfile& p )
{
	j = nlohmann::json{
		{ "model",    p.model },
		{ "spacing",  p.spacing },
		{ "diameter", p.diameter },
		{ "height",   p.height },
		{ "padding",  p.padding }
	};
}

// RivetNode
void Sprocket::to_json( nlohmann::json& j, const Sprocket::RivetNode& p ) 
{
	j = nlohmann::json{
		{ "next",       p.next },
		{ "prev",       p.prev },
		{ "face",       p.face },
		{ "u",          p.v },
		{ "v",          p.v },
		{ "w",          p.w },
		{ "faceOffset", p.faceOffset },
		{ "profile",    p.profile },
		{ "flags",      p.flags }
	};
}

// Rivets
void Sprocket::to_json( nlohmann::json& j, const Sprocket::Rivets& p ) 
{
	j = nlohmann::json{
		{ "profiles", p.profiles },
		{ "nodes",    p.nodes }
	};
}

// SerializedFace
void Sprocket::to_json( nlohmann::json& j, const Sprocket::SerializedFace& p ) 
{
	j = nlohmann::json{
		{ "v",  p.vertices },
		{ "t",  p.thicknesses },
		{ "tm", p.thickenModes.u32 },
		{ "te", p.thickenEdgeIndicies.u64 }
	};
}

// MeshBlueprint
void Sprocket::to_json( nlohmann::json& j, const Sprocket::MeshBlueprint& p ) 
{
	j = nlohmann::json{
		{ "majorVersion", p.majorVersion },
		{ "minorVersion", p.minorVersion },
		{ "vertices",     p.vertexPositions },
		{ "edges",        p.serializedEdges },
		{ "edgeFlags",    p.serializedEdgeFlags },
		{ "faces",        p.serializedFaces }
	};
}

// MeshData
void Sprocket::to_json( nlohmann::json& j, const Sprocket::MeshData& p ) 
{
	j = nlohmann::json{
		{ "v",           p.v },
		{ "name",        p.name },
		{ "smoothAngle", p.smoothAngle },
		{ "gridSize",    p.gridSize },
		{ "format",      p.format },
		{ "mesh",        p.mesh },
		{ "rivets",      p.rivets }
	};
}

// PlateStructureMesh
void Sprocket::to_json( nlohmann::json& j, const Sprocket::PlateStructureMesh& p ) 
{
	j = nlohmann::json{
		{ "vuid",     p.vuid },
		{ "type",     p.type },
		{ "meshData", p.meshData }
	};
}

// RivetTypeProfile
void Sprocket::from_json( const nlohmann::json& j, Sprocket::RivetTypeProfile& p )
{
	j.at( "model" ).get_to( p.model );
	j.at( "spacing" ).get_to( p.spacing );
	j.at( "diameter" ).get_to( p.diameter );
	j.at( "height" ).get_to( p.height );
	j.at( "padding" ).get_to( p.padding );
}

// RivetNode
void Sprocket::from_json( const nlohmann::json& j, Sprocket::RivetNode& p )
{
	j.at( "next" ).get_to( p.next );
	j.at( "prev" ).get_to( p.prev );
	j.at( "face" ).get_to( p.face );
	j.at( "u" ).get_to( p.u );
	j.at( "v" ).get_to( p.v );
	j.at( "w" ).get_to( p.w );
	j.at( "faceOffset" ).get_to( p.faceOffset );
	j.at( "profile" ).get_to( p.profile );
	j.at( "flags" ).get_to( p.flags );
}

// Rivets
void Sprocket::from_json( const nlohmann::json& j, Sprocket::Rivets& p )
{
	j.at( "profiles" ).get_to( p.profiles );
	j.at( "nodes" ).get_to( p.nodes );
}

// SerializedFace
void Sprocket::from_json( const nlohmann::json& j, Sprocket::SerializedFace& p ) 
{
	j.at( "v" ).get_to( p.vertices );
	j.at( "t" ).get_to( p.thicknesses );
	j.at( "tm" ).get_to( p.thickenModes.u32 );
	j.at( "te" ).get_to( p.thickenEdgeIndicies.u64 );
}

// MeshBlueprint
void Sprocket::from_json( const nlohmann::json& j, Sprocket::MeshBlueprint& p ) 
{
	j.at( "majorVersion" ).get_to( p.majorVersion );
	j.at( "minorVersion" ).get_to( p.minorVersion );
	j.at( "vertices" ).get_to( p.vertexPositions );
	j.at( "edges" ).get_to( p.serializedEdges );
	j.at( "edgeFlags" ).get_to( p.serializedEdgeFlags );
	j.at( "faces" ).get_to( p.serializedFaces );
}

// MeshData
void Sprocket::from_json( const nlohmann::json& j, Sprocket::MeshData& p ) 
{
	j.at( "v" ).get_to( p.v );
	j.at( "name" ).get_to( p.name );
	j.at( "smoothAngle" ).get_to( p.smoothAngle );
	j.at( "gridSize" ).get_to( p.gridSize );
	j.at( "format" ).get_to( p.format );
	j.at( "mesh" ).get_to( p.mesh );
	j.at( "rivets" ).get_to( p.rivets );
}

// PlateStructureMesh
void Sprocket::from_json( const nlohmann::json& j, Sprocket::PlateStructureMesh& p ) 
{
	j.at( "vuid" ).get_to( p.vuid );
	j.at( "type" ).get_to( p.type );
	j.at( "meshData" ).get_to( p.meshData );
}

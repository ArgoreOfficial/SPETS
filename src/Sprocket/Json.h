#pragma once

#include "PlateMesh/PlateMesh.h"
#include "Era.h"

#include <nlohmann/json.hpp>

namespace Sprocket {

void to_json( nlohmann::json& _json, const Sprocket::RivetTypeProfile& _p );
void to_json( nlohmann::json& _json, const Sprocket::RivetNode& _p );
void to_json( nlohmann::json& _json, const Sprocket::Rivets& _p );
void to_json( nlohmann::json& _json, const Sprocket::SerializedFace& _p );
void to_json( nlohmann::json& _json, const Sprocket::MeshBlueprint& _p );
void to_json( nlohmann::json& _json, const Sprocket::MeshData& _p );
void to_json( nlohmann::json& _json, const Sprocket::PlateStructureMesh& _p );
void to_json( nlohmann::json& _json, const Sprocket::EraDefinition& _p );

void from_json( const nlohmann::json& _json, Sprocket::RivetTypeProfile& _p );
void from_json( const nlohmann::json& _json, Sprocket::RivetNode& _p );
void from_json( const nlohmann::json& _json, Sprocket::Rivets& _p );
void from_json( const nlohmann::json& _json, Sprocket::SerializedFace& _p );
void from_json( const nlohmann::json& _json, Sprocket::MeshBlueprint& _p );
void from_json( const nlohmann::json& _json, Sprocket::MeshData& _p );
void from_json( const nlohmann::json& _json, Sprocket::PlateStructureMesh& _p );
void from_json( const nlohmann::json& _json, Sprocket::EraDefinition& _p );

}
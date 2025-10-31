#pragma once

#include "PlateMesh/PlateMesh.h"

#include <nlohmann/json.hpp>

namespace Sprocket {

void to_json( nlohmann::json& j, const Sprocket::RivetTypeProfile& p );
void to_json( nlohmann::json& j, const Sprocket::RivetNode& p );
void to_json( nlohmann::json& j, const Sprocket::Rivets& p );
void to_json( nlohmann::json& j, const Sprocket::SerializedFace& p );
void to_json( nlohmann::json& j, const Sprocket::MeshBlueprint& p );
void to_json( nlohmann::json& j, const Sprocket::MeshData& p );
void to_json( nlohmann::json& j, const Sprocket::PlateStructureMesh& p );

void from_json( const nlohmann::json& j, Sprocket::RivetTypeProfile& p );
void from_json( const nlohmann::json& j, Sprocket::RivetNode& p );
void from_json( const nlohmann::json& j, Sprocket::Rivets& p );
void from_json( const nlohmann::json& j, Sprocket::SerializedFace& p );
void from_json( const nlohmann::json& j, Sprocket::MeshBlueprint& p );
void from_json( const nlohmann::json& j, Sprocket::MeshData& p );
void from_json( const nlohmann::json& j, Sprocket::PlateStructureMesh& p );


}
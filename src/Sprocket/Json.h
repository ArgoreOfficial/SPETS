#pragma once

#include <Sprocket/Sprocket.h>
#include <Sprocket/PlateMesh/PlateMesh.h>
#include <Sprocket/CustomBattle.h>
#include <Sprocket/Era.h>

#include <nlohmann/json.hpp>

namespace Sprocket {

// Blueprints

void to_json( nlohmann::json& _json, const Sprocket::RivetTypeProfile& _p );
void from_json( const nlohmann::json& _json, Sprocket::RivetTypeProfile& _p );

void to_json( nlohmann::json& _json, const Sprocket::RivetNode& _p );
void from_json( const nlohmann::json& _json, Sprocket::RivetNode& _p );

void to_json( nlohmann::json& _json, const Sprocket::Rivets& _p );
void from_json( const nlohmann::json& _json, Sprocket::Rivets& _p );

void to_json( nlohmann::json& _json, const Sprocket::SerializedFace& _p );
void from_json( const nlohmann::json& _json, Sprocket::SerializedFace& _p );

void to_json( nlohmann::json& _json, const Sprocket::MeshBlueprint& _p );
void from_json( const nlohmann::json& _json, Sprocket::MeshBlueprint& _p );

void to_json( nlohmann::json& _json, const Sprocket::MeshData& _p );
void from_json( const nlohmann::json& _json, Sprocket::MeshData& _p );

void to_json( nlohmann::json& _json, const Sprocket::SerializableMesh& _p );
void from_json( const nlohmann::json& _json, Sprocket::SerializableMesh& _p );

void to_json( nlohmann::json& _json, const Sprocket::VehicleBlueprintHeader& _p );
void from_json( const nlohmann::json& _json, Sprocket::VehicleBlueprintHeader& _p );

void to_json( nlohmann::json& _json, const Sprocket::VehicleBlueprint& _p );
void from_json( const nlohmann::json& _json, Sprocket::VehicleBlueprint& _p );

// Custom Battles

void to_json( nlohmann::json& _json, const Sprocket::EnvironmentConfig& _p );
void from_json( const nlohmann::json& _json, Sprocket::EnvironmentConfig& _p );

void to_json( nlohmann::json& _json, const Sprocket::UnitDefinition& _p );
void from_json( const nlohmann::json& _json, Sprocket::UnitDefinition& _p );

void to_json( nlohmann::json& _json, const Sprocket::UnitInstanceInfo& _p );
void from_json( const nlohmann::json& _json, Sprocket::UnitInstanceInfo& _p );

void to_json( nlohmann::json& _json, const Sprocket::TeamDefinition& _p );
void from_json( const nlohmann::json& _json, Sprocket::TeamDefinition& _p );

void to_json( nlohmann::json& _json, const Sprocket::CustomBattleConfig& _p );
void from_json( const nlohmann::json& _json, Sprocket::CustomBattleConfig& _p );

// Era

void to_json( nlohmann::json& _json, const Sprocket::EraDefinition& _p );
void from_json( const nlohmann::json& _json, Sprocket::EraDefinition& _p );

}
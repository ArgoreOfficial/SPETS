#pragma once

#include "../json/json.hpp"

//////////////////////////////////////////////////////////////////

/* only use these to quickly generate, then expand the function */

// begin
#define beginSerialize nlohmann::ordered_json serialize() { return {

// serialize
#define serializeT( _t ) { #_t, _t },
#define serializeC( _t ) { #_t, _t.serialize() },

// end
#define endSerialize	}; }

//////////////////////////////////////////////////////////////////

struct sVersion
{
	int Major;
	int Minor;

	//----------------------------------------------------------//

	nlohmann::ordered_json serialize()
	{
		return {
			{ "Major", Major },
			{ "Minor", Minor },
		};
	}

};

//////////////////////////////////////////////////////////////////

struct sTraverse
{
	double torque = 750.0;
	double ratio = 45.0;
	int    type = 1;
	double resistance = 0.5;

	//----------------------------------------------------------//

	nlohmann::ordered_json serialize()
	{
		return {
			{ "torque", torque },
			{ "ratio", ratio },
			{ "type", type },
			{ "resistance", resistance },
		}; 
	}

};

//////////////////////////////////////////////////////////////////

struct sTurret
{
	bool enabled = false;
	sVersion    version{ 0, 4 };
	sTraverse   traverse{};
	double      radius       = 0.001;
	double      height       = 0.001;
	int         ringArmour   = 1;
	double      basketVolume = 0.0;
	const char* ring         = "9192fd19364dc7f4d9b1cd351f9ff840";
	double      min          = -360.0;
	double      max          = 360.0;

	//----------------------------------------------------------//

	nlohmann::ordered_json serialize()
	{
		if ( !enabled ) return nullptr;

		return {
			{ "version", version.serialize() },
			{ "traverse", traverse.serialize() },
			{ "radius", radius },
			{ "height", height },
			{ "ringArmour", ringArmour },
			{ "basketVolume", basketVolume },
			{ "ring", ring },
			{ "min", min },
			{ "max", max },
		};
	}

};

//////////////////////////////////////////////////////////////////

struct sCompartmentData
{
	sVersion version{ 0, 1 };
	std::vector<double> points{ 
		  1.0, -0.0, -1.0,
		 -1.0, -0.0,  1.0,
		 -1.0, -0.0, -1.0,
		  1.0, -0.0, -1.0,
		  1.0, -0.0,  1.0,
		 -1.0, -0.0,  1.0 };

	std::vector<std::vector<int>> sharedPoints{ { 0, 3 }, { 1, 5 }, { 4 }, { 2 } };
	std::vector<int> thicknessMap{ 1,1,1,1,1,1 };
	std::vector<std::vector<int>> faceMap{ { 2, 1, 0 }, { 5, 4, 3 } };
	double smooth = 0.0;

	//----------------------------------------------------------//

	nlohmann::ordered_json serialize()
	{
		return {
			{ "version", version.serialize() },
			{ "points", points },
			{ "sharedPoints", sharedPoints },
			{ "thicknessMap", thicknessMap },
			{ "faceMap", faceMap },
			{ "smooth", smooth },
		};
	}
};

//////////////////////////////////////////////////////////////////

struct sCompartment
{
public:
	sVersion version{ 0, 3 };
	std::string name{ "debug_cube" };
	int ID              = 0;
	int parentID        = -1;
	int flags           = 3;          /* 3:hull, 4:turret */
	double displacement = 0;
	double armourVolume = 0;

	std::vector<double> pos{ 0.0, 0.0, 0.0 };
	std::vector<double> rot{ 0.0, 0.0, 0.0 };
	sTurret turret;
	nlohmann::json genID;   /* not sure what these are used for */
	nlohmann::json genData;
	sCompartmentData compartment;

	//----------------------------------------------------------//

	nlohmann::ordered_json serialize()
	{
		return {
			{ "version", version.serialize() },
			{ "name", name },
			{ "ID", ID },
			{ "parentID", parentID },
			{ "flags", flags },
			{ "displacement", displacement },
			{ "armourVolume", armourVolume },
			{ "pos", pos },
			{ "rot", rot },
			{ "turret", turret.serialize() },
			{ "genID", genID },
			{ "genData", genData },
			{ "compartment", compartment.serialize() },
		};
	}

};

//////////////////////////////////////////////////////////////////

struct sBlueprint
{
	std::string id{ "Compartment" };
	std::string data;
	std::string metaData;

	//----------------------------------------------------------//

	beginSerialize
		serializeT( id )
		serializeT( data )
		serializeT( metaData )
	endSerialize

};

//////////////////////////////////////////////////////////////////

struct sHeader
{
	std::string name{ "import" };
	std::string game_version{ "0.127" };
	int mass = 1;
	std::string era{ "Latewar" };
	std::string class_str;
	std::string desc;

	nlohmann::ordered_json serialize()
	{
		return {
			{ "name", name },
			{ "gameVersion", game_version },
			{ "mass", mass },
			{ "era", era },
			{ "class", class_str },
			{ "desc", desc },
		};
	}
};

//////////////////////////////////////////////////////////////////

struct sVehicle
{
	sVersion version{1,0};
	std::string name{ "import" };
	sHeader header;
	std::vector<nlohmann::ordered_json> blueprints{};
	std::vector<int> ext{};

	nlohmann::ordered_json serialize()
	{
		return {
			{ "version", version.serialize() },
			{ "name", name },
			{ "header", header.serialize() },
			{ "blueprints", blueprints },
			{ "ext", ext },
		};
	}
};
#pragma once

#include <string>
#include <format>
#include <vector>

namespace Sprocket {

struct EraDefinition
{
	std::string v = "0.0"; // version?
	std::string name = "Coldwar";
	std::string start = "1945.09.03";
	bool playable = true;
	int mediumVehicleMass = 18000;
	int heavyVehicleMass = 36000;

	void setStartDate( uint16_t _year, uint8_t _month, uint8_t _day ) {
		start = std::format( "{:04d}.{:02d}.{:02d}", _year, _month, _day );
	}
};

std::vector<EraDefinition> getAllEras();
EraDefinition getEra( const std::string& _name );
void saveEra( const EraDefinition& _era );

}
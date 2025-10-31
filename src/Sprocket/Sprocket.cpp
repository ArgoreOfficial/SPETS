#include "Sprocket.h"
#include "Json.h"

#include <nlohmann/json.hpp>

#include <fstream>

bool Sprocket::loadCompartmentFromFile( const std::string& _path, MeshData& _out )
{
	std::ifstream f( _path );
	if ( !f.is_open() )
		return false;

	nlohmann::json json = nlohmann::json::parse( f );
	f.close(); // immediately close file

	if ( json[ "v" ] == "2.0" )
	{
		printf( "Vehicle Blueprint, NOT IMPLEMENTED YET" );
		return false;
	}
	
	_out = json.get<Sprocket::MeshData>();
	
	return true;
}

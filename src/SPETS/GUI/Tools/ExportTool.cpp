#include "ExportTool.h"

#include <Sprocket/Sprocket.h>
#include <Sprocket/Error.h>
#include <SPETS/GUI/ApplicationHub.h>

#include <format>

extern SPETS::ApplicationHubFrame* g_frame;

void SPETS::ExportTool::onRunTool()
{
}

void SPETS::ExportTool::checkedExport( const std::filesystem::path& _path )
{
	std::string status = std::format( "Exporting {}", _path.filename().string() );
	printf( "%s\n", status.c_str() );
	SPETS::g_frame->SetStatusText( status );

	Sprocket::BlueprintType type = Sprocket::getBlueprintFileType( _path );
	if ( type == Sprocket::BlueprintType_Compartment )
	{
		Sprocket::MeshData mesh;
		if ( Sprocket::loadBlueprintFromFile( _path.string(), mesh ) )
			Sprocket::exportBlueprintToFile( mesh, _path.filename().replace_extension() );
	}
	else if ( type == Sprocket::BlueprintType_Vehicle )
	{
		Sprocket::VehicleBlueprint vehicle;
		if ( Sprocket::loadBlueprintFromFile( _path.string(), vehicle ) )
			Sprocket::exportBlueprintToFile( vehicle );
	}
	else
	{
		SPROCKET_PUSH_ERROR( "'{}' is not a valid blueprint file", _path.filename().string() );
	}
}

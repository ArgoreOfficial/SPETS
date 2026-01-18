#include "ExportTool.h"

#include <wx/wx.h>

#include <Sprocket/Sprocket.h>
#include <Sprocket/Error.h>
#include <SPETS/GUI/ApplicationHub.h>

#include <format>

extern SPETS::ApplicationHubFrame* g_frame;

void SPETS::ExportTool::onRunTool()
{
	std::string currentFaction = Sprocket::getCurrentFaction();
	std::string blueprintsDir = ( Sprocket::getFactionPath( currentFaction ) / "Blueprints" ).string();

	wxFileDialog openFileDialog = wxFileDialog(
		g_frame,
		wxEmptyString, blueprintsDir, wxEmptyString,
		"Sprocket Blueprints (*.blueprint)|*.blueprint",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE
	);

	openFileDialog.SetFilterIndex( 0 );
	if ( openFileDialog.ShowModal() != wxID_OK )
		return;

	wxArrayString paths;
	openFileDialog.GetFilenames( paths );

	// export files
	for ( size_t i = 0; i < paths.Count(); i++ )
		checkedExport( paths[ i ].ToStdWstring() );

	// check for any errors
	if ( Sprocket::hasError() )
	{
		std::string s = std::format( "{} errors generated. Check log.", Sprocket::getNumErrors() );
		SPETS::g_frame->SetStatusText( s );

		printf( "Errors generated:\n" );
		while ( Sprocket::hasError() )
			printf( "    %s\n", Sprocket::popError().c_str() );
	}
	else
	{
		std::string s = std::format( "{} blueprints exported.", paths.GetCount() );
		SPETS::g_frame->SetStatusText( s );
	}
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

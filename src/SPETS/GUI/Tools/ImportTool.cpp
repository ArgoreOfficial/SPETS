#include "ImportTool.h"

#include <wx/wx.h>

#include <Sprocket/Sprocket.h>
#include <Sprocket/Error.h>
#include <SPETS/GUI/ApplicationHub.h>

#include <format>

extern SPETS::ApplicationHubFrame* g_frame;

void SPETS::ImportTool::onRunTool()
{
	std::string currentFaction = Sprocket::getCurrentFaction();
	std::string blueprintsDir = ( Sprocket::getFactionPath( currentFaction ) / "Blueprints" ).string();

	wxFileDialog openFileDialog = wxFileDialog(
		this,
		wxEmptyString, blueprintsDir, wxEmptyString,
		"Blueprints (*.blueprint)|*.blueprint",
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

void SPETS::ImportTool::checkedImport( const std::filesystem::path& _path, const std::string& _faction )
{
	std::string status = std::format( "Importing {}", _path.filename().string() );
	printf( "%s\n", status.c_str() );
	SPETS::g_frame->SetStatusText( status );

	const std::string name = _path.filename().replace_extension().string();

	Sprocket::MeshData outMesh;
	outMesh.name = name;

	if ( Sprocket::createCompartmentFromMesh( _path.string(), outMesh ) )
		Sprocket::saveCompartmentToFaction( outMesh, _faction, name );
}

void SPETS::ImportTool::quickImportFiles( const std::vector<std::string>& _files )
{
	const std::string currentFaction = Sprocket::getCurrentFaction();

	// import meshes
	for ( size_t i = 0; i < _files.size(); i++ )
		checkedImport( _files[ i ], currentFaction );

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
		std::string s = std::format( "{} meshes imported into '{}'.", _files.size(), Sprocket::getCurrentFaction() );
		SPETS::g_frame->SetStatusText( s );
	}
}


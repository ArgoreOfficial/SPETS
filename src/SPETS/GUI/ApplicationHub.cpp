
#include "ApplicationHub.h"

#include <Sprocket/Sprocket.h>
#include <Sprocket/Error.h>

#include <SPETS/GUI/HubWindowDropTarget.h>

SPETS::ApplicationHubFrame* SPETS::g_frame = nullptr;

SPETS::ApplicationHubFrame::ApplicationHubFrame() : 
	wxFrame( nullptr, wxID_ANY, "SPETS", wxDefaultPosition, { 400, 250 }, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN )
{
	const int ID_TOOL_QUICK_IMPORT = 1;
	const int ID_TOOL_QUICK_EXPORT = 2;
	const int ID_TOOL_MERGE = 3;

	wxMenu* menuFile = new wxMenu();
	{
		menuFile->Append( wxID_OPEN, "&Open...\tCtrl-O", "Open a .blueprint file" );
		// Bind( wxEVT_MENU, &ApplicationHubFrame::OnExit, this, wxID_OPEN );
		
		menuFile->AppendSeparator();

		menuFile->Append( wxID_EXIT );
		Bind( wxEVT_MENU, &ApplicationHubFrame::OnExit, this, wxID_EXIT );
	}
	
	wxMenu* menuTools = new wxMenu();
	{
		menuTools->Append( ID_TOOL_QUICK_IMPORT, "&Quick Import...\tCtrl-I", "Quickly import into the current faction" );
		Bind( wxEVT_MENU, &ApplicationHubFrame::OnQuickImport, this, ID_TOOL_QUICK_IMPORT );

		menuTools->Append( ID_TOOL_QUICK_EXPORT, "&Quick Export...\tCtrl-E", "Quickly export a blueprint" );
		Bind( wxEVT_MENU, &ApplicationHubFrame::OnQuickExport, this, ID_TOOL_QUICK_EXPORT );

		menuTools->Append( ID_TOOL_MERGE, "&Merge Compartments", "Merge multiple compartments into one" );
		Bind( wxEVT_MENU, &ApplicationHubFrame::OnMerge, this, ID_TOOL_MERGE );

		menuTools->AppendSeparator();

		// load lua-based tools here
		menuTools->Append( wxID_ANY, "&Placeholder", "This is a placeholder for visuals" );
		menuTools->Append( wxID_ANY, "&Placeholder2", "later these will be used for Lua tools" );
	}

	wxMenu* menuHelp = new wxMenu();
	{
		menuHelp->Append( wxID_ABOUT );
		Bind( wxEVT_MENU, &ApplicationHubFrame::OnAbout, this, wxID_ABOUT );
	}

	wxMenuBar* menuBar = new wxMenuBar();
	{
		menuBar->Append( menuFile, "&File" );
		menuBar->Append( menuTools, "&Tools" );
		menuBar->Append( menuHelp, "&Help" );
		SetMenuBar( menuBar );
	}

	CreateStatusBar();
	SetStatusText( std::string( "SPETS " ) + SPETS::VERSION_STR );

	wxStaticBitmap* staticBitmap = new wxStaticBitmap( m_panel, wxID_ANY, wxNullBitmap );
	staticBitmap->SetDropTarget( new HubWindowDropTarget( staticBitmap, { "file.png", wxBITMAP_TYPE_PNG }, { "download.png", wxBITMAP_TYPE_PNG } ) );
	staticBitmap->SetSize( m_panel->GetSize() );
}

// TODO: replace with lua tool
static void checkedImport( const std::filesystem::path& _path, const std::string& _faction )
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

// TODO: replace with lua tool
static void checkedExport( const std::filesystem::path& _path )
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

// TODO: replace with lua tool
static void quickImportHelper( const wxArrayString& _filenames )
{
	const std::string currentFaction = Sprocket::getCurrentFaction();

	// import meshes
	for ( size_t i = 0; i < _filenames.GetCount(); i++ )
		checkedImport( _filenames[ i ].ToStdWstring(), currentFaction );
	
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
		std::string s = std::format( "{} meshes imported into '{}'.", _filenames.GetCount(), Sprocket::getCurrentFaction() );
		SPETS::g_frame->SetStatusText( s );
	}

}

void SPETS::ApplicationHubFrame::OnQuickImport( wxCommandEvent& event )
{
	std::string currentFaction = Sprocket::getCurrentFaction();

	wxFileDialog openFileDialog = wxFileDialog(
		this,
		wxEmptyString, wxEmptyString, wxEmptyString,
		"All Files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE
	);

	openFileDialog.SetFilterIndex( 0 );
	if ( openFileDialog.ShowModal() != wxID_OK )
		return;

	wxArrayString paths;
	openFileDialog.GetFilenames( paths );
	quickImportHelper( paths );
	
}

void SPETS::ApplicationHubFrame::OnQuickExport( wxCommandEvent& _event )
{
	std::string currentFaction = Sprocket::getCurrentFaction();
	std::string blueprintsDir = (Sprocket::getFactionPath( currentFaction ) / "Blueprints" ).string();

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

bool SPETS::HubWindowDropTarget::OnDropFiles( wxCoord _x, wxCoord _y, const wxArrayString& _filenames )
{
	printf( "Dropping %llu files\n", _filenames.GetCount() );

	if ( m_surface )
		m_surface->SetBitmap( m_bitmap );

	const std::string currentFaction = Sprocket::getCurrentFaction();

	for ( size_t i = 0; i < _filenames.GetCount(); i++ )
	{
		std::filesystem::path p = _filenames[ i ].ToStdWstring();

		if ( p.extension() == ".blueprint" )
			checkedExport( p );
		else
			checkedImport( p, currentFaction );
	}

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
		std::string s = std::format( "{} meshes imported into '{}'.", _filenames.GetCount(), Sprocket::getCurrentFaction() );
		SPETS::g_frame->SetStatusText( s );
	}

	return true;
}

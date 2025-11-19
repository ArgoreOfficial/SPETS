
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
		m_importTool = new ImportTool();
		m_exportTool = new ExportTool();

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
	staticBitmap->SetDropTarget( new HubWindowDropTarget( staticBitmap, { "dat/file.png", wxBITMAP_TYPE_PNG }, { "dat/download.png", wxBITMAP_TYPE_PNG } ) );
	staticBitmap->SetSize( m_panel->GetSize() );
}

void SPETS::ApplicationHubFrame::onDropFiles( const std::vector<std::filesystem::path>& _paths )
{
	const std::string currentFaction = Sprocket::getCurrentFaction();

	size_t imported = 0;
	size_t exported = 0;

	for ( size_t i = 0; i < _paths.size(); i++ )
	{
		std::filesystem::path p = _paths[ i ];

		if ( p.extension() == ".blueprint" )
		{
			m_exportTool->checkedExport( p );
			exported++;
		}
		else
		{
			m_importTool->checkedImport( p, currentFaction );
			imported++;
		}
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
		std::string status = "";

		if( imported > 0 )
			status += std::format( "{} meshes imported. ", imported );

		if( exported > 0 )
			status += std::format( "{} meshes exported. ", exported );

		SPETS::g_frame->SetStatusText( status );
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

	std::vector<std::string> paths{};

	// toStdVectorString
	{
		wxArrayString wxpaths;
		openFileDialog.GetFilenames( wxpaths );

		for ( size_t i = 0; i < wxpaths.GetCount(); i++ )
			paths.push_back( wxpaths[ i ].ToStdString() );
	}
	
	m_importTool->quickImportFiles( paths );
	
}

void SPETS::ApplicationHubFrame::OnMerge( wxCommandEvent& event )
{

}

bool SPETS::HubWindowDropTarget::OnDropFiles( wxCoord _x, wxCoord _y, const wxArrayString& _filenames )
{
	printf( "Dropping %llu files\n", _filenames.GetCount() );

	if ( m_surface )
		m_surface->SetBitmap( m_bitmap );

	std::vector<std::filesystem::path> paths;
	for ( size_t i = 0; i < _filenames.GetCount(); i++ )
		paths.push_back( _filenames[ i ].ToStdWstring() );
	g_frame->onDropFiles( paths );

	return true;
}

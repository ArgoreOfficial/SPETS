#pragma once

#include <wx/wx.h>

#include <SPETS/Util.h>
#include <Sprocket/Sprocket.h>

namespace SPETS {

class Frame : public wxFrame
{
public:
	Frame() : wxFrame{ nullptr, wxID_ANY, "SPETS" } {
		wxMenu* menuFile = new wxMenu();
		menuFile->Append( ID_OPEN, "&Open...\tCtrl-O", "Open a .blueprint file" );
		menuFile->AppendSeparator();
		menuFile->Append( wxID_EXIT );

		wxMenu* menuTools = new wxMenu();
		menuTools->Append( ID_TOOL_QUICK_IMPORT, "&Quick Import...\tCtrl-I", "Quickly import into the current faction" );
		menuTools->Append( ID_TOOL_QUICK_EXPORT, "&Quick Export...\tCtrl-E", "Quickly export a blueprint" );
		menuTools->Append( ID_TOOL_MERGE,        "&Merge Compartments", "Merge multiple compartments into one" );

		wxMenu* menuHelp = new wxMenu();
		menuHelp->Append( wxID_ABOUT );

		wxMenuBar* menuBar = new wxMenuBar();
		menuBar->Append( menuFile,  "&File" );
		menuBar->Append( menuTools, "&Tools" );
		menuBar->Append( menuHelp,  "&Help" );
		SetMenuBar( menuBar );

		CreateStatusBar();
		SetStatusText( std::string("SPETS ") + SPETS::VERSION_STR );

		//Bind( wxEVT_MENU, &Frame::OnHello, this, ID_OPEN );
		
		Bind( wxEVT_MENU, &Frame::OnQuickImport, this, ID_TOOL_QUICK_IMPORT );
		Bind( wxEVT_MENU, &Frame::OnMerge, this, ID_TOOL_MERGE );

		Bind( wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT );
		Bind( wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT );
	}

private:
	void OnAbout( wxCommandEvent& event ) {
		std::string version = "SPETS Version: ";
		version += SPETS::VERSION_STR;
		wxMessageBox( version, "About SPETS", wxOK | wxICON_INFORMATION );
	}

	void OnExit( wxCommandEvent& event ) {
		Close( true );
	}

	void OnQuickImport( wxCommandEvent& event ) {
		std::string currentFaction = Sprocket::getCurrentFaction();
		wxLogMessage( "The Current Faction is %s", currentFaction.c_str() );
	}
	
	void OnMerge( wxCommandEvent& event ) {
		wxLogMessage( "add more rivets" );
	}

	inline static const int ID_OPEN = 1;
	inline static const int ID_TOOL_QUICK_IMPORT = 2;
	inline static const int ID_TOOL_QUICK_EXPORT = 3;
	inline static const int ID_TOOL_MERGE = 4;
};

class Application : public wxApp
{
	bool OnInit() override { 
		return ( new Frame )->Show(); 
	}
};

}

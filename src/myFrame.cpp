#include <iostream>

#include "myApp.h"
#include "myFrame.h"

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

using namespace std;


wxBEGIN_EVENT_TABLE( myFrame, wxFrame )
    EVT_MENU( ID_AddFiles,   myFrame::OnAddFiles )
    EVT_MENU( wxID_EXIT,  myFrame::OnExit )
    EVT_MENU( wxID_ABOUT, myFrame::OnAbout )
    EVT_BUTTON( button_addfilesID, myFrame::OnAddFiles)
    EVT_BUTTON( button_removeID, myFrame::OnRemove)
    EVT_BUTTON( button_browseID, myFrame::OnBrowse)
    EVT_BUTTON( button_exportID, myFrame::OnExport)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP( myApp );

myFrame::myFrame( const wxString& title, const wxPoint& pos, const wxSize& size ) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxFileName f( wxStandardPaths::Get().GetUserDataDir() );
    m_user_home = f.GetPath();

    wxColour back_colour1 = wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND );
    wxColour back_colour = back_colour1;
    back_colour1 = wxColour( back_colour1.Red()*0.75, back_colour1.Green()*0.75, back_colour1.Blue() );

	wxMenu *menuFile = new wxMenu;
    menuFile->Append( ID_AddFiles, "&Add Files\tCtrl-A", "Add files to be converted" );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT );
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append( wxID_ABOUT );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( "Add some files." );

    // Build layout.
    wxPanel *panel_left = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600, 640 ) );
    panel_left->SetBackgroundColour( wxColour( 80,80,200 ) );
    wxPanel *panel_buttons = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600, 100 ) );
    panel_buttons->SetBackgroundColour( back_colour );

    wxBoxSizer *sizer_fl = new wxBoxSizer( wxVERTICAL );
    sizer_fl->Add( panel_left, 1, wxEXPAND | wxALL );
    sizer_fl->Add( panel_buttons, 0, wxEXPAND | wxALL );

    // right panel
    wxPanel *panel_right = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600, 640 ) );
    panel_right->SetBackgroundColour( back_colour1 );

    wxBoxSizer *sizer = new wxBoxSizer( wxHORIZONTAL );
    sizer->Add( sizer_fl, 1, wxEXPAND | wxALL, 5 );
    sizer->Add( panel_right, 0, wxEXPAND | wxALL, 5 );
    this->SetSizerAndFit( sizer );

    // Add Left controls
    listview = new wxListView( panel_left, wxID_ANY, wxDefaultPosition, wxSize( 600, 400 ) );
    listview->InsertColumn( 0, "Filename" );
    listview->SetColumnWidth( 0, 600 );

    wxBoxSizer *sizer_listview = new wxBoxSizer( wxVERTICAL );
    sizer_listview->Add( listview, 1, wxEXPAND | wxALL );
    panel_left->SetSizerAndFit( sizer_listview );

    // Buttons
    wxButton *button_Add = new wxButton( panel_buttons, button_addfilesID, "Add files" );
    wxButton *button_Remove = new wxButton( panel_buttons, button_removeID, "Remove ALL" );

    wxBoxSizer *sizer_buttons = new wxBoxSizer( wxHORIZONTAL );
    sizer_buttons->Add( button_Add, 1, wxEXPAND | wxALL, 3 );
    sizer_buttons->Add( button_Remove, 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 3 );
    panel_buttons->SetSizerAndFit( sizer_buttons );

    // Add right Controls - Export options
    formats.Add( "Apple Prores HQ" );
    formats.Add( "Avid DNxHR HQX" );
    formats.Add( "Sony DV avi" );
    formats.Add( "h265 AAC" );
    formats.Add( "h264 AAC" );

    wxStaticText *label_format = new wxStaticText( panel_right, wxID_ANY, "Export Format" );
    combo_format = new wxChoice( panel_right, wxID_ANY, wxDefaultPosition, wxDefaultSize, formats );
    combo_format->Select( 0 );

    wxStaticText *label_location = new wxStaticText( panel_right, wxID_ANY, "Export Location" );
    te_location = new wxTextCtrl( panel_right, wxID_ANY, m_user_home + "/Videos" );
    wxButton *button_browse = new wxButton( panel_right, button_browseID, "Browse" );
    // Export button
    button_export = new wxButton( panel_right, button_exportID, "Export", wxDefaultPosition, wxSize(-1,100) );
    button_export->SetBackgroundColour( wxColour(20,80,20) );

    // right side sizeer layout
    wxBoxSizer *sizer_export = new wxBoxSizer( wxVERTICAL );
    sizer_export->Add( label_format, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 3 );
    sizer_export->Add( combo_format, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 3 );
    sizer_export->Add( label_location, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 3 );
    sizer_export->Add( te_location, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 3 );
    sizer_export->Add( button_browse, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 3 );
    sizer_export->Add( button_export, 0, wxEXPAND | wxHORIZONTAL | wxLEFT | wxRIGHT | wxTOP, 20 );
    panel_right->SetSizer( sizer_export );

    Centre();
}

void myFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void myFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "ffConvert v0.1 by Lee A. Stripp", "ffConvert", wxOK | wxICON_INFORMATION );
}

void myFrame::OnAddFiles( wxCommandEvent& event )
{
	wxFileDialog *OpenDialog = new wxFileDialog(
		this, _("Add files to convert"), m_user_home, wxEmptyString,
		_("All files (*.*)|*.*"), wxFD_MULTIPLE, wxDefaultPosition );

	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxArrayString paths;
        OpenDialog->GetPaths( paths );

        for( int i=0; i<paths.GetCount(); i++ )
        {
            //cout << paths[i] << endl;
            listview->InsertItem( 0, paths[i] );
        }
	}
	OpenDialog->Destroy();
}

void myFrame::OnRemove( wxCommandEvent& event )
{
    listview->DeleteAllItems();

    /* BROKEN - works but creates an issue when selecting rows later. CHASHES.
    wxArrayInt row_numbers_to_delete;
    long itemIndex = -1;

    while( (itemIndex = listview->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND )
    {
        // Add the selected item index
        row_numbers_to_delete.Add( itemIndex );
    }

    // Delete in reverse order.
    for( long n = ( row_numbers_to_delete.GetCount() -1 ); n >= 0; n-- )
    {
        // Remove it from the listctrl.
        listview->DeleteItem( row_numbers_to_delete[ n ] );
    }
    */
}

void myFrame::OnBrowse( wxCommandEvent& event )
{
    wxDirDialog *dir = new wxDirDialog( this, _("Choose export location"), te_location->GetValue(), 0, wxDefaultPosition );

	if( dir->ShowModal() ==  wxID_OK )
	{
        te_location->SetValue( dir->GetPath() );
    }
    dir->Destroy();
}

void myFrame::OnExport( wxCommandEvent& event )
{
    button_export->Enable( false );
    button_export->SetBackgroundColour( wxColour(200,50,50) );
    SetStatusText( "Exporting files..." );

    long itemIndex = -1;
    while( (itemIndex = listview->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND )
    {
        wxString fullfilepath = listview->GetItemText( itemIndex );
        cout << "Export : " << fullfilepath << endl;

        wxFileName f = fullfilepath;
        wxString filename_noext = f.GetName();
        wxString path = te_location->GetValue();
        //cout << "filename : " << filename_noext << endl;
        //cout << "Path   : " << path << endl;

        /*
        formats.Add( "Apple Prores HQ" );
        formats.Add( "Avid DNxHR HQX" );
        formats.Add( "Sony DV avi" );
        formats.Add( "h265 AAC" );
        formats.Add( "h264 AAC" );
        */
        wxString cmd;
        switch( combo_format->GetSelection() )
        {
        case 0: // Apple Prores HQ
            cmd = "ffmpeg -threads 8 -probesize 5000000 -i '" +
            fullfilepath +
            "' -c:v prores_ks -profile:v 3 -qscale:v 9 -vendor ap10 -pix_fmt yuv422p10le -acodec pcm_s24le -ar 48k -y '" +
            path + "/" +
            filename_noext + ".mov'";
            break;

        case 1: // Avid DNxHR HQX
            cmd = "ffmpeg -threads 8 -i '" +
            fullfilepath +
            "' -c:v dnxhd -vf 'format=yuv422p10le' -profile:v dnxhr_hqx -b:v 746M -c:a pcm_s16le '" +
            path + "/" + filename_noext +
             ".mov'";
            break;

        case 2: // Sony DV avi
            cmd = "ffmpeg -threads 8 -i '" +
            fullfilepath +
            "' -vcodec dvvideo -s 720x576 -acodec pcm_s16le '" +
            path + "/" + filename_noext +
            ".avi'";
            break;

        case 3: // h265 AAC
            cmd = "ffmpeg -threads 8 -i '" +
            fullfilepath +
            "' -c:v libx265 -c:a aac '" +
            path + "/" + filename_noext +
            ".mov'";
            break;

        case 4: // h264 AAC
            cmd = "ffmpeg -threads 8 -i '" +
            fullfilepath +
            "' -c:v libx264 -c:a aac '" +
            path + "/" + filename_noext +
            ".mov'";
            break;

        default:
            cout << "Unknown format" << endl;
            break;
        }

        // execute cmd
        cout << "cmd : " << cmd << endl;
        if(! cmd.empty() )
        {
            // long wxExecute 	( 	const wxString &  	command, wxArrayString &  	output )
            wxArrayString output;
            wxExecute( cmd, output );
        }
    } // while(itemIndex)

    SetStatusText( "Done!" );
    button_export->SetBackgroundColour( wxColour(20,80,20) );
    button_export->Enable( true );

    Refresh();
}

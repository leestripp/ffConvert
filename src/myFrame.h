#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>

enum {
    ID_AddFiles = wxID_HIGHEST + 1,
    button_addfilesID,
    button_removeID,
    button_browseID,
    button_exportID
};


class myFrame : public wxFrame
{
public:
    myFrame( const wxString& title, const wxPoint& pos, const wxSize& size );

private:
    void OnExit( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );

    // Buttons
    void OnAddFiles( wxCommandEvent& event );
    void OnRemove( wxCommandEvent& event );
    void OnBrowse( wxCommandEvent& event );
    void OnExport( wxCommandEvent& event );

    // global controls
    wxListView *listview;
    wxTextCtrl *te_location;
    wxButton *button_export;
    wxArrayString formats;
    wxChoice *combo_format;

    wxDECLARE_EVENT_TABLE();
};

#endif // MYFRAME_H

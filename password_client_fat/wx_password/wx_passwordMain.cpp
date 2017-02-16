/***************************************************************
 * Name:      wx_passwordMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    developer_1
 * Created:   2017-02-15
 * Copyright: developer_1
 * License:   GPL2
 **************************************************************/

#include "wx_passwordMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(wx_passwordDialog)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wx_passwordDialog)
const long wx_passwordDialog::ID_TXT_WELCOME_TEXT = wxNewId();
const long wx_passwordDialog::ID_BTN_PASSWORD_LIST = wxNewId();
const long wx_passwordDialog::ID_STATICLINE2 = wxNewId();
const long wx_passwordDialog::ID_BTN_ABOUT = wxNewId();
const long wx_passwordDialog::ID_STATICLINE1 = wxNewId();
const long wx_passwordDialog::ID_BTN_QUIT = wxNewId();
//*)

BEGIN_EVENT_TABLE(wx_passwordDialog,wxDialog)
    //(*EventTable(wx_passwordDialog)
    //*)
END_EVENT_TABLE()

wx_passwordDialog::wx_passwordDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wx_passwordDialog)
    Create(parent, id, _("wx password"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    txtWelcomeText = new wxStaticText(this, ID_TXT_WELCOME_TEXT, _("Welcome to\nwx password"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TXT_WELCOME_TEXT"));
    wxFont txtWelcomeTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !txtWelcomeTextFont.Ok() ) txtWelcomeTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    txtWelcomeTextFont.SetPointSize(20);
    txtWelcomeText->SetFont(txtWelcomeTextFont);
    BoxSizer1->Add(txtWelcomeText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    btnOpenPasswordList = new wxButton(this, ID_BTN_PASSWORD_LIST, _("Password list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_PASSWORD_LIST"));
    BoxSizer2->Add(btnOpenPasswordList, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer2->Add(StaticLine2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    btnAbout = new wxButton(this, ID_BTN_ABOUT, _("About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_ABOUT"));
    BoxSizer2->Add(btnAbout, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer2->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    btnQuit = new wxButton(this, ID_BTN_QUIT, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_QUIT"));
    BoxSizer2->Add(btnQuit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    BoxSizer1->Add(BoxSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BTN_PASSWORD_LIST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wx_passwordDialog::OnbtnOpenPasswordListClick);
    Connect(ID_BTN_ABOUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wx_passwordDialog::OnAbout);
    Connect(ID_BTN_QUIT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wx_passwordDialog::OnQuit);
    //*)
}

wx_passwordDialog::~wx_passwordDialog()
{
    //(*Destroy(wx_passwordDialog)
    //*)
}

void wx_passwordDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wx_passwordDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = "Welcome to wx password manager client\nAuthor: developer_1, Licence: GPL2";
    wxMessageBox(msg);
}

void wx_passwordDialog::OnbtnOpenPasswordListClick(wxCommandEvent& event)
{
// TODO (developer_1 #1 #2017-02-15): open password list in modal mode
    wx_password_list* list_window = new wx_password_list(this, wxID_ANY);
    list_window->ShowModal();
}

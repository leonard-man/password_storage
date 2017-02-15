#include "wx_password_entry.h"

//(*InternalHeaders(wx_password_entry)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(wx_password_entry)
const long wx_password_entry::ID_LBL_NAME = wxNewId();
const long wx_password_entry::ID_TXT_NAME = wxNewId();
const long wx_password_entry::ID_LBL_DESC = wxNewId();
const long wx_password_entry::ID_TXT_DESC = wxNewId();
const long wx_password_entry::ID_LBL_URL = wxNewId();
const long wx_password_entry::ID_TXT_URL = wxNewId();
const long wx_password_entry::ID_LBL_EMAIL = wxNewId();
const long wx_password_entry::ID_TXT_EMAIL = wxNewId();
const long wx_password_entry::ID_LBL_USERNAME = wxNewId();
const long wx_password_entry::ID_TXT_USERNAME = wxNewId();
const long wx_password_entry::ID_LBL_PASSWORD = wxNewId();
const long wx_password_entry::ID_TXT_PASSWORD = wxNewId();
const long wx_password_entry::ID_LBL_PWD_HNT = wxNewId();
const long wx_password_entry::ID_TXT_PSW_HNT = wxNewId();
const long wx_password_entry::ID_LBL_EMPTY = wxNewId();
//*)

BEGIN_EVENT_TABLE(wx_password_entry,wxDialog)
	//(*EventTable(wx_password_entry)
	//*)
END_EVENT_TABLE()

wx_password_entry::wx_password_entry(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wx_password_entry)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(369,312));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	grdszrPasswordEntry = new wxGridSizer(8, 2, 0, 0);
	lbl_name = new wxStaticText(this, ID_LBL_NAME, _("Name"), wxDefaultPosition, wxSize(50,-1), 0, _T("ID_LBL_NAME"));
	grdszrPasswordEntry->Add(lbl_name, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_name = new wxTextCtrl(this, ID_TXT_NAME, _("name"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_NAME"));
	grdszrPasswordEntry->Add(txt_name, 2, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lbl_description = new wxStaticText(this, ID_LBL_DESC, _("Description"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_DESC"));
	grdszrPasswordEntry->Add(lbl_description, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_description = new wxTextCtrl(this, ID_TXT_DESC, _("description"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_DESC"));
	grdszrPasswordEntry->Add(txt_description, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lbl_login_url = new wxStaticText(this, ID_LBL_URL, _("Login url"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_URL"));
	grdszrPasswordEntry->Add(lbl_login_url, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_login_url = new wxTextCtrl(this, ID_TXT_URL, _("login_url"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_URL"));
	grdszrPasswordEntry->Add(txt_login_url, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lbl_email = new wxStaticText(this, ID_LBL_EMAIL, _("Email"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_EMAIL"));
	grdszrPasswordEntry->Add(lbl_email, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_email = new wxTextCtrl(this, ID_TXT_EMAIL, _("email"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_EMAIL"));
	grdszrPasswordEntry->Add(txt_email, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lbl_username = new wxStaticText(this, ID_LBL_USERNAME, _("Username"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_USERNAME"));
	grdszrPasswordEntry->Add(lbl_username, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_username = new wxTextCtrl(this, ID_TXT_USERNAME, _("username"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_USERNAME"));
	grdszrPasswordEntry->Add(txt_username, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lbl_password = new wxStaticText(this, ID_LBL_PASSWORD, _("Password"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_PASSWORD"));
	grdszrPasswordEntry->Add(lbl_password, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_password = new wxTextCtrl(this, ID_TXT_PASSWORD, _("password"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_PASSWORD"));
	grdszrPasswordEntry->Add(txt_password, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lbl_password_hint = new wxStaticText(this, ID_LBL_PWD_HNT, _("Password hint"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_PWD_HNT"));
	grdszrPasswordEntry->Add(lbl_password_hint, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txt_password_hint = new wxTextCtrl(this, ID_TXT_PSW_HNT, _("password hint"), wxDefaultPosition, wxSize(260,-1), 0, wxDefaultValidator, _T("ID_TXT_PSW_HNT"));
	grdszrPasswordEntry->Add(txt_password_hint, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lbl_empty = new wxStaticText(this, ID_LBL_EMPTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_LBL_EMPTY"));
	grdszrPasswordEntry->Add(lbl_empty, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	std_dlg_button_sizer = new wxStdDialogButtonSizer();
	std_dlg_button_sizer->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	std_dlg_button_sizer->AddButton(new wxButton(this, wxID_SAVE, wxEmptyString));
	std_dlg_button_sizer->Realize();
	grdszrPasswordEntry->Add(std_dlg_button_sizer, 0, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	SetSizer(grdszrPasswordEntry);
	SetSizer(grdszrPasswordEntry);
	Layout();
	//*)
}

wx_password_entry::~wx_password_entry()
{
	//(*Destroy(wx_password_entry)
	//*)
}


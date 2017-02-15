#ifndef WX_PASSWORD_ENTRY_H
#define WX_PASSWORD_ENTRY_H

//(*Headers(wx_password_entry)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class wx_password_entry: public wxDialog
{
	public:

		wx_password_entry(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wx_password_entry();

		//(*Declarations(wx_password_entry)
		wxTextCtrl* txt_password;
		wxStaticText* lbl_empty;
		wxStaticText* lbl_login_url;
		wxStaticText* lbl_password_hint;
		wxTextCtrl* txt_password_hint;
		wxStaticText* lbl_name;
		wxTextCtrl* txt_description;
		wxStaticText* lbl_password;
		wxGridSizer* grdszrPasswordEntry;
		wxStaticText* lbl_username;
		wxStdDialogButtonSizer* std_dlg_button_sizer;
		wxTextCtrl* txt_name;
		wxTextCtrl* txt_username;
		wxTextCtrl* txt_email;
		wxTextCtrl* txt_login_url;
		wxStaticText* lbl_description;
		wxStaticText* lbl_email;
		//*)

	protected:

		//(*Identifiers(wx_password_entry)
		static const long ID_LBL_NAME;
		static const long ID_TXT_NAME;
		static const long ID_LBL_DESC;
		static const long ID_TXT_DESC;
		static const long ID_LBL_URL;
		static const long ID_TXT_URL;
		static const long ID_LBL_EMAIL;
		static const long ID_TXT_EMAIL;
		static const long ID_LBL_USERNAME;
		static const long ID_TXT_USERNAME;
		static const long ID_LBL_PASSWORD;
		static const long ID_TXT_PASSWORD;
		static const long ID_LBL_PWD_HNT;
		static const long ID_TXT_PSW_HNT;
		static const long ID_LBL_EMPTY;
		//*)

	private:

		//(*Handlers(wx_password_entry)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

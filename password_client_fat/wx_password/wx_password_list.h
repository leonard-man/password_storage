#ifndef WX_PASSWORD_LIST_H
#define WX_PASSWORD_LIST_H

//(*Headers(wx_password_list)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/listbox.h>
//*)

class wx_password_list: public wxDialog
{
	public:

		wx_password_list(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~wx_password_list();

		//(*Declarations(wx_password_list)
		wxListBox* lstPasswordList;
		wxBoxSizer* pwlMainBoxSizer;
		wxBoxSizer* pwlListButtonSizer;
		wxButton* btnDeletePasswordEntry;
		wxButton* btnRefreshPasswordList;
		wxButton* btnEditPasswordEntry;
		wxButton* btnAddPasswordEntry;
		//*)

	protected:

		//(*Identifiers(wx_password_list)
		static const long ID_LST_PASSWORD_LIST;
		static const long ID_BTN_REFRESH_PWD_LIST;
		static const long ID_BTN_ADD_PWD_ENTRY;
		static const long ID_BTN_EDIT_PWD_ENTRY;
		static const long ID_BTN_PWD_ENTRY_DELETE;
		//*)

	private:

		//(*Handlers(wx_password_list)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

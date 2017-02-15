/***************************************************************
 * Name:      wx_passwordMain.h
 * Purpose:   Defines Application Frame
 * Author:    developer_1
 * Created:   2017-02-15
 * Copyright: developer_1
 * License:   GPL2
 **************************************************************/

#ifndef WX_PASSWORDMAIN_H
#define WX_PASSWORDMAIN_H

//(*Headers(wx_passwordDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class wx_passwordDialog: public wxDialog
{
    public:

        wx_passwordDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~wx_passwordDialog();

    private:

        //(*Handlers(wx_passwordDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbtnOpenPasswordListClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(wx_passwordDialog)
        static const long ID_TXT_WELCOME_TEXT;
        static const long ID_BTN_PASSWORD_LIST;
        static const long ID_STATICLINE2;
        static const long ID_BTN_ABOUT;
        static const long ID_STATICLINE1;
        static const long ID_BTN_QUIT;
        //*)

        //(*Declarations(wx_passwordDialog)
        wxButton* btnQuit;
        wxStaticLine* StaticLine2;
        wxButton* btnAbout;
        wxBoxSizer* BoxSizer2;
        wxStaticText* txtWelcomeText;
        wxButton* btnOpenPasswordList;
        wxStaticLine* StaticLine1;
        wxBoxSizer* BoxSizer1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WX_PASSWORDMAIN_H

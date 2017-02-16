/***************************************************************
 * Name:      wx_passwordApp.cpp
 * Purpose:   Code for Application Class
 * Author:    developer_1
 * Created:   2017-02-15
 * Copyright: developer_1
 * License:   GPL2
 **************************************************************/

#include "wx_passwordApp.h"

//(*AppHeaders
#include "wx_passwordMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wx_passwordApp);

bool wx_passwordApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wx_passwordDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)

    return wxsOK;

}

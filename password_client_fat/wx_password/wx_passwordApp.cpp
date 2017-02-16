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
    utils = new utility();
    string configuration_path = utils->get_config_path();

    // Load XML configuration file using DOMConfigurator
    DOMConfigurator::configure(configuration_path + "Log4cxxConfig.xml");

    LOG4CXX_INFO(passwordApp, "-- program start --");
    LOG4CXX_INFO(passwordApp, "password storage project - fat client component");
    LOG4CXX_INFO(passwordApp, "-------------------------------------------");
    LOG4CXX_INFO(passwordApp, "wxWidgets fat client where target server is deployed at VPS which is online all the time");
    LOG4CXX_INFO(passwordApp, "client needs to show stored passwords and enable CRUD of password information");
    LOG4CXX_INFO(passwordApp, "");

    LOG4CXX_INFO(passwordApp, "log4cxx configuration successfully parsed");

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

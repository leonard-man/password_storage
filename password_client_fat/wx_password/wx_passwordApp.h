/***************************************************************
 * Name:      wx_passwordApp.h
 * Purpose:   Defines Application Class
 * Author:    developer_1
 * Created:   2017-02-15
 * Copyright: developer_1
 * License:   GPL2
 **************************************************************/

#ifndef WX_PASSWORDAPP_H
#define WX_PASSWORDAPP_H

#include <wx/app.h>
#include "utility.h"
#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace std;

LoggerPtr passwordApp(Logger::getLogger("wx_passwordApp::OnInit()"));

class wx_passwordApp : public wxApp
{
    public:
        virtual bool OnInit();
    private:
        utility* utils = nullptr;
};

#endif // WX_PASSWORDAPP_H

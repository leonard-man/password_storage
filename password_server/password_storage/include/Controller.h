#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

#include "Utility.h"
#include "DatabaseLayer.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/* class which binds everything together */
class Controller
{
    public:
        Controller();
        virtual ~Controller();
        void set_utils(Utility* utils);
        Utility* get_utils();
        void set_database_layer(DatabaseLayer* data_layer);
        DatabaseLayer* get_database_layer();

    protected:
    private:
        Utility* m_utils = nullptr;
        DatabaseLayer* m_data_layer = nullptr;
};

#endif // CONTROLLER_H

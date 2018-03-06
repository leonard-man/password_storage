#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <libconfig.h++>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <tinyxml2.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;
using namespace libconfig;
using namespace tinyxml2;

class utility
{
    public:
        utility();
        virtual ~utility();
        sqlite3* get_database_instance();
        bool read_configuration();
        string get_config_path();
        string get_server_ip();
        bool read_message(string message);
    protected:
    private:
        bool m_configParsed;
        sqlite3* m_database = nullptr;
        string root_path;
        string server_ip_v4;
        bool parse_xml_string();
};

#endif // UTILITY_H

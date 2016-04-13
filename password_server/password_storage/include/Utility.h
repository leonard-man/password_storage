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

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;
using namespace libconfig;

class Utility
{
    public:
        Utility();
        virtual ~Utility();
        sqlite3* get_database_instance();
        bool read_configuration();
        string get_config_path();
    protected:
    private:
        bool m_configParsed;
        sqlite3* m_database = nullptr;
        string root_path;
};

#endif // UTILITY_H

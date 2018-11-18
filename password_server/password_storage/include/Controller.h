#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

#include "PasswordEntry.h"
#include "Utility.h"
#include "DatabaseLayer.h"
#include "SendPackage.h"
#include "ReceivePackage.h"
#include "MessageParsingResult.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class Controller
{
    public:
        // constructor and destructor
        Controller();
        virtual ~Controller();
        // functions
        void set_utils(Utility* utils);
        Utility* get_utils();
        void set_database_layer(DatabaseLayer* data_layer);
        DatabaseLayer* get_database_layer();
        ReceivePackage* create_receive_package();
        void set_received_package(ReceivePackage* package_received);
        SendPackage* get_send_package();
        void parse_package_received();
        void create_message_parsing_result();
    protected:
    private:
        // fields
        Utility* m_utils = nullptr;
        DatabaseLayer* m_data_layer = nullptr;
        ReceivePackage* m_receive_package = nullptr;
        SendPackage* m_send_package = nullptr;
        MessageParsingResult* m_message_parsing_result = nullptr;
        // functions
        string list_all_passwords();
};

#endif // CONTROLLER_H

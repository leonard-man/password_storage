#include "Controller.h"
#include "CommunicationLayer.h"
#include "DatabaseLayer.h"
#include "Utility.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;

// Define static logger variable
LoggerPtr universalLogger(Logger::getLogger("universal"));

int main()
{
    cout << "password storage project - server component" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Linux server daemon where target deployment is VPS which is online all the time" << endl;
    cout << "server needs to store passwords and communicate password information" << endl;
    cout << "to clients, rich and thin" << endl;
    cout << "" << endl;
    cout << "" << endl;

    Controller* controller = new Controller();

    Utility* util = new Utility();
    controller->set_utils(util);
    util = nullptr;

    string configuration_path = controller->get_utils()->get_config_path();
    // Load XML configuration file using DOMConfigurator
    DOMConfigurator::configure(configuration_path + "Log4cxxConfig.xml");

    LOG4CXX_INFO(universalLogger, "-- program start --");
    LOG4CXX_INFO(universalLogger, "password storage project - server component");
    LOG4CXX_INFO(universalLogger, "-------------------------------------------");
    LOG4CXX_INFO(universalLogger, "Linux server daemon where target deployment is VPS which is online all the time");
    LOG4CXX_INFO(universalLogger, "server needs to store passwords and communicate password information");
    LOG4CXX_INFO(universalLogger, "to clients, rich and thin");
    LOG4CXX_INFO(universalLogger, "");


    LOG4CXX_INFO(universalLogger, "log4cxx configuration successfully parsed");

    // TODO (sgnjidic#9#2016-04-12): remove - this is for testing purposes, only
    controller->get_utils()->get_database_instance();

    CommunicationLayer* comm = new CommunicationLayer();
    controller->set_communication_layer(comm);
    comm = nullptr;

    delete(controller);

    LOG4CXX_INFO(universalLogger, "-- program end --");

    return 0;
}
// TODO (sgnjidic #1 #2016-04-12): next steps:
// TODO (sgnjidic #1 #2016-04-12): * start with datalayer with CRUD API - should work with designated database
// TODO (sgnjidic #1 #2016-04-13): - learn how to use SQLite API to manipulate SQL data
// TODO (sgnjidic #1 #2016-04-12): * start with communication layer - learn a bit about socket programming and network streaming
// TODO (sgnjidic #1 #2016-04-12): * integrate datalayer and communication layer - make sure data is streamed back and forts as expected
// TODO (sgnjidic #1 #2016-04-12): * move to thick client - make sure it enables basic CRUD
// TODO (sgnjidic #1 #2016-04-12): * when thick client with basic CRUD is in place, implement encryption


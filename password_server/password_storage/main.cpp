#include "Controller.h"
#include "CommunicationLayer.h"
#include "DatabaseLayer.h"
#include "Utility.h"
#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace std;

LoggerPtr main_cpp(Logger::getLogger("main.cpp"));

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

    LOG4CXX_INFO(main_cpp, "-- program start --");
    LOG4CXX_INFO(main_cpp, "password storage project - server component");
    LOG4CXX_INFO(main_cpp, "-------------------------------------------");
    LOG4CXX_INFO(main_cpp, "Linux server daemon where target deployment is VPS which is online all the time");
    LOG4CXX_INFO(main_cpp, "server needs to store passwords and communicate password information");
    LOG4CXX_INFO(main_cpp, "to clients, rich and thin");
    LOG4CXX_INFO(main_cpp, "");


    LOG4CXX_INFO(main_cpp, "log4cxx configuration successfully parsed");

    CommunicationLayer* comm = new CommunicationLayer();
    controller->set_communication_layer(comm);
    comm = nullptr;

    DatabaseLayer* db = new DatabaseLayer();
    db->set_database(controller->get_utils()->get_database_instance());
    controller->set_database_layer(db);
    db = nullptr;

    // for testing purposes, only
    PasswordEntry pwd;
    pwd.set_id(6);
    pwd.set_name("Srećko Gnjidić");
    pwd.set_description("update - test entry");
    pwd.set_email("sgnjidic@inet.hr");
    pwd.set_login_url("ubuntu vm workstation");
    pwd.set_username("sgnjidic");
    pwd.set_password("Fido11");
    pwd.set_password_hint("pekingese eleven");
    // pwd.set_password_hint("tralala...");

    // controller->get_database_layer()->insert_password_entry(pwd);

    // controller->get_database_layer()->delete_password_entry(pwd);

    controller->get_database_layer()->update_password_entry(pwd);

    delete(controller);

    LOG4CXX_INFO(main_cpp, "-- program end --\n");

    return 0;
}

// TODO (sgnjidic #9 #2016-04-12): next steps:
// TODO (sgnjidic #9 #2016-04-12): * start with datalayer with CRUD API - should work with designated database
// TODO (sgnjidic #9 #2016-04-13): - learn how to use SQLite API to manipulate SQL data
// TODO (sgnjidic #9 #2016-04-12): * start with communication layer - learn a bit about socket programming and network streaming
// TODO (sgnjidic #9 #2016-04-12): * integrate datalayer and communication layer - make sure data is streamed back and forts as expected
// TODO (sgnjidic #9 #2016-04-12): * move to thick client - make sure it enables basic CRUD
// TODO (sgnjidic #9 #2016-04-12): * when thick client with basic CRUD is in place, implement encryption


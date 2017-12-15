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

    CommunicationLayer* comm = new CommunicationLayer();

    Controller* controller = new Controller();
    comm->set_controller(controller);

    Utility* util = new Utility();
    comm->get_controller()->set_utils(util);
    util = nullptr;

    string configuration_path = comm->get_controller()->get_utils()->get_config_path();

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

    LOG4CXX_INFO(main_cpp, "xml_template_single: " + controller->get_utils()->get_single_password_template());
    LOG4CXX_INFO(main_cpp, "xml_template_bracket_all: " + controller->get_utils()->get_all_passwords_bracket_template());



    SendPackage* sendPackage = new SendPackage();
    sendPackage->set_is_sent(false);
    sendPackage->set_payload("Welcome to password_storage server!");

    comm->set_send_package(sendPackage);

    // controller->set_communication_layer(comm);

    DatabaseLayer* db = new DatabaseLayer();
    db->set_database(controller->get_utils()->get_database_instance());
    comm->get_controller()->set_database_layer(db);
    db = nullptr;

    // make payload  - xml with all password entries
    // send it to fat client for unmarshalling and rendering into GUI

    // vector<PasswordEntry*> result = controller-> get_database_layer()->get_all_password_entries();

    int something = comm->start_server();

    delete(comm);


    /*
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
    */

    /*
    PasswordEntry another_pwd;
    another_pwd.set_id(12);
    another_pwd.set_name("Srećko Gnjidić");
    another_pwd.set_description("update - test entry 2");
    another_pwd.set_email("sgnjidic@inet.hr");
    another_pwd.set_login_url("ubuntu vm server");
    another_pwd.set_username("s.gnjidic");
    another_pwd.set_password("MacakP1ko");
    another_pwd.set_password_hint("dot marked cat");
    */

    // controller->get_database_layer()->insert_password_entry(another_pwd);

    // controller->get_database_layer()->delete_password_entry(pwd);

    /*
    PasswordEntry* old_entity = controller->get_database_layer()->update_password_entry(pwd);
    LOG4CXX_INFO(main_cpp, "old_entry - column 0: " + old_entity->get_id());
    LOG4CXX_INFO(main_cpp, "old_entry - column 1: " + old_entity->get_name());
    LOG4CXX_INFO(main_cpp, "old_entry - column 2: " + old_entity->get_description());
    LOG4CXX_INFO(main_cpp, "old_entry - column 3: " + old_entity->get_email());
    LOG4CXX_INFO(main_cpp, "old_entry - column 4: " + old_entity->get_login_url());
    LOG4CXX_INFO(main_cpp, "old_entry - column 5: " + old_entity->get_username());
    LOG4CXX_INFO(main_cpp, "old_entry - column 6: " + old_entity->get_password());
    LOG4CXX_INFO(main_cpp, "old_entry - column 7: " + old_entity->get_password_hint());
    delete(old_entity);
    */

    /*
    PasswordEntry* result = controller->get_database_layer()->get_password_entry(another_pwd.get_id());

    LOG4CXX_INFO(main_cpp, "password_entry - column 0: " + to_string(result->get_id()));
    LOG4CXX_INFO(main_cpp, "password_entry - column 1: " + result->get_name());
    LOG4CXX_INFO(main_cpp, "password_entry - column 2: " + result->get_description());
    LOG4CXX_INFO(main_cpp, "password_entry - column 3: " + result->get_email());
    LOG4CXX_INFO(main_cpp, "password_entry - column 4: " + result->get_login_url());
    LOG4CXX_INFO(main_cpp, "password_entry - column 5: " + result->get_username());
    LOG4CXX_INFO(main_cpp, "password_entry - column 6: " + result->get_password());
    LOG4CXX_INFO(main_cpp, "password_entry - column 7: " + result->get_password_hint());
    delete(result);
    */

    /*

    for(auto &it : result)
    {
        LOG4CXX_INFO(main_cpp, "password_entry - column 0: " + to_string(it->get_id()));
        LOG4CXX_INFO(main_cpp, "password_entry - column 1: " + it->get_name());
        LOG4CXX_INFO(main_cpp, "password_entry - column 2: " + it->get_description());
        LOG4CXX_INFO(main_cpp, "password_entry - column 3: " + it->get_email());
        LOG4CXX_INFO(main_cpp, "password_entry - column 4: " + it->get_login_url());
        LOG4CXX_INFO(main_cpp, "password_entry - column 5: " + it->get_username());
        LOG4CXX_INFO(main_cpp, "password_entry - column 6: " + it->get_password());
        LOG4CXX_INFO(main_cpp, "password_entry - column 7: " + it->get_password_hint());
    }

    for(auto &it : result)
    {
        delete(it);
    }

    result.clear();

    */

    LOG4CXX_INFO(main_cpp, "-- program end --\n");

    return 0;
}

// TODO (developer_1 #5 #2017-02-19): next steps - from password storage main.cpp:
// TODO (developer_1 #8 #2017-03-09): based on commands, action should be taken, return package prepared
// TODO (developer_1 #8 #2017-03-09): return package should be sent back to caller
// TODO (developer_1 #8 #2017-02-19): * integrate database and communication
// TODO (developer_1 #8 #2017-02-19): * - implement get all password entities
// TODO (developer_1 #8 #2017-02-19): * - implement get password entity (by id)
// TODO (developer_1 #8 #2017-02-19): * - implement create password entity
// TODO (developer_1 #8 #2017-02-19): * - implement edit password entity
// TODO (developer_1 #8 #2017-02-19): * - implement delete password entity
// TODO (developer_1 #8 #2017-02-19): * implement basic CRUD with fat client
// TODO (developer_1 #8 #2017-02-19): * when thick client with basic CRUD is in place, implement encryption

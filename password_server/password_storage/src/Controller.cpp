#include "Controller.h"

LoggerPtr ControllerLogger = Logger::getLogger("Controller");

Controller::Controller()
{
    // constructor
}

Controller::~Controller()
{
    if (m_data_layer != nullptr)
    {
        delete(m_data_layer);
    }

    if (m_utils != nullptr)
    {
        delete(m_utils);
    }
}
void Controller::create_message_parsing_result()
{
    if (m_message_parsing_result != nullptr)
    {
        delete(m_message_parsing_result);
    }

    m_message_parsing_result = new MessageParsingResult();
}

void Controller::set_utils(Utility* utils)
{
    m_utils = utils;
    //
}

Utility* Controller::get_utils()
{
    return m_utils;
}

void Controller::set_database_layer(DatabaseLayer* data_layer)
{
    m_data_layer = data_layer;
}

DatabaseLayer* Controller::get_database_layer()
{
    return m_data_layer;
}

ReceivePackage* Controller::create_receive_package()
{
    if(m_receive_package != nullptr)
    {
        delete(m_receive_package);
    }

    m_receive_package = new ReceivePackage();

    return m_receive_package;
}

void Controller::set_received_package(ReceivePackage* package_received)
{
    if(m_receive_package != nullptr)
    {
        delete(m_receive_package);
    }

    m_receive_package = package_received;

    LOG4CXX_INFO(ControllerLogger, "Controller::package_received");
}

SendPackage* Controller::get_send_package()
{
    if(m_send_package != nullptr)
    {
        delete(m_send_package);
    }

    SendPackage* send_package = new SendPackage();
    string parsing_result_message = m_message_parsing_result->get_parsing_result_message();
    send_package->set_payload(parsing_result_message);

    m_send_package = send_package;
    LOG4CXX_INFO(ControllerLogger, "Controller::send_package_ready: " + m_send_package->get_payload());

    return m_send_package;
}

void Controller::parse_package_received()
{
    LOG4CXX_INFO(ControllerLogger, "Controller: parsing received package");

    create_message_parsing_result();
    string string_message;

    if(m_receive_package->get_payload() == "﻿<?xml version=\"1.0\" encoding=\"UTF-8\"?><list_all_passwords>")
    {
        string_message = list_all_passwords();
        m_message_parsing_result->set_parsing_result_message(string_message);

        LOG4CXX_INFO(ControllerLogger, "Controller: test implementation of <list_all_passwords>.");
    }
}

string Controller::list_all_passwords()
{
    string result = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><password_list>";

    vector<PasswordEntry*> all_passwords = m_data_layer->get_all_password_entries();

    for(int i = 0; (unsigned)i < all_passwords.size(); i++)
    {
        result = result + "<password_entry>";
        result = result + "<password_id>";
        result = result + to_string(all_passwords[i]->get_id());
        result = result + "</password_id>";
        result = result + "<password_name>";
        result = result + all_passwords[i]->get_name();
        result = result + "</password_name>";
        result = result + "<password_description>";
        result = result + all_passwords[i]->get_description();
        result = result + "</password_description>";
        result = result + "<password_email>";
        result = result + all_passwords[i]->get_email();
        result = result + "</password_email>";
        result = result + "<password_login_url>";
        result = result + all_passwords[i]->get_login_url();
        result = result + "</password_login_url>";
        result = result + "<password_username>";
        result = result + all_passwords[i]->get_username();
        result = result + "</password_username>";
        result = result + "<password_password>";
        result = result + all_passwords[i]->get_password();
        result = result + "</password_password>";
        result = result + "<password_password_hint>";
        result = result + all_passwords[i]->get_password_hint();
        result = result + "</password_password_hint></password_entry>";
    }

    result = result + "</password_list>";

    all_passwords.clear();

    return result;
}

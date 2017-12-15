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

bool Controller::set_received_package(ReceivePackage* package_received)
{
    if(received_package != nullptr)
    {
        delete(received_package);
    }

    received_package = package_received;

    LOG4CXX_INFO(ControllerLogger, "Controller::package_received");

    return parse_package_received() == nullptr;
}

SendPackage* Controller::get_send_package()
{
    if(send_package != nullptr)
    {
        delete(send_package);
    }

    MessageParsingResult* result = parse_package_received();
    SendPackage* send_package = new SendPackage();
    send_package->set_payload(result->get_parsing_result_message());

    LOG4CXX_INFO(ControllerLogger, "Controller::send_package_ready: " + send_package->get_payload());

    return send_package;
}

MessageParsingResult* Controller::parse_package_received()
{
    LOG4CXX_INFO(ControllerLogger, "Controller: parsing received package");

    MessageParsingResult* mp_result = new MessageParsingResult();
    string string_message;

    // TODO (developer_1 #1 #2017-12-09): hardcode implementation of <list_all_passwords> to see the code flow
    if(received_package->get_payload() == "<list_all_passwords>")
    {
        string_message = list_all_passwords();
        mp_result->set_parsing_result_message(string_message);

        LOG4CXX_INFO(ControllerLogger, "Controller: test implementation of <list_all_passwords>.");
    }

    return mp_result;
}

string Controller::list_all_passwords()
{
    string result = "<password_list>";

    vector<PasswordEntry*> all_passwords = m_data_layer->get_all_password_entries();

    for(int i=0; i<all_passwords.size(); i++)
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

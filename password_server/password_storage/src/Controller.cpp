#include "Controller.h"

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
    // TODO (developer_1 #3 #2017-11-12): log entry here
}

SendPackage* Controller::get_send_package()
{
    if(send_package != nullptr)
    {
        delete(send_package);
    }

    MessageParsingResult* result = parse_package_received();
    // TODO (developer_1 #3 #2017-11-12): log entry here

    // TODO (developer_1 #3 #2017-11-05): interpret result
}

MessageParsingResult* Controller::parse_package_received()
{
    // TODO (developer_1 #3 #2017-11-12): log entry here

    return nullptr;
}

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

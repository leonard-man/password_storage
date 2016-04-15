#include "PasswordEntry.h"

LoggerPtr PasswordEntryLogger = Logger::getLogger("PasswordEntry");

PasswordEntry::PasswordEntry()
{
    //ctor
}

PasswordEntry::~PasswordEntry()
{
    //dtor
}

unsigned int PasswordEntry::get_id()
{
    return m_ID;
}

void PasswordEntry::set_id(unsigned int val)
{
    m_ID = val;
}

string PasswordEntry::get_name()
{
    return m_name;
}

void PasswordEntry::set_name(string val)
{
    m_name = val;
}

string PasswordEntry::get_description()
{
    return m_description;
}

void PasswordEntry::set_description(string val)
{
    m_description = val;
}

string PasswordEntry::get_login_url()
{
    return m_login_url;
}

void PasswordEntry::set_login_url(string val)
{
    m_login_url = val;
}

string PasswordEntry::get_email()
{
    return m_email;
}

void PasswordEntry::set_email(string val)
{
    m_email = val;
}

string PasswordEntry::get_username()
{
    return m_username;
}

void PasswordEntry::set_username(string val)
{
    m_username = val;
}

string PasswordEntry::get_password() {
    return m_password;
}

void PasswordEntry::set_password(string val)
{
    m_password = val;
}

string PasswordEntry::get_password_hint()
{
    return m_password_hint;
}

void PasswordEntry::set_password_hint(string val)
{
    m_password_hint = val;
}

#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class PasswordEntry
{
    public:
        PasswordEntry();
        virtual ~PasswordEntry();
        unsigned int get_id() { return m_ID; }
        void set_id(unsigned int val) { m_ID = val; }
        string get_name() { return m_name; }
        void set_name(string val) { m_name = val; }
        string get_description() { return m_description; }
        void set_description(string val) { m_description = val; }
        string get_login_url() { return m_login_url; }
        void set_login_url(string val) { m_login_url = val; }
        string get_email() { return m_email; }
        void set_email(string val) { m_email = val; }
        string get_username() { return m_username; }
        void set_username(string val) { m_username = val; }
        string get_password() { return m_password; }
        void set_password(string val) { m_password = val; }
        string get_password_hint() { return m_password_hint; }
        void set_password_hint(string val) { m_password_hint = val; }
    protected:
    private:
        unsigned int m_ID;
        string m_name;
        string m_description;
        string m_login_url;
        string m_email;
        string m_username;
        string m_password;
        string m_password_hint;
};

#endif // PASSWORDENTRY_H

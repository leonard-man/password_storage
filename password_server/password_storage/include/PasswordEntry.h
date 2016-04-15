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
        unsigned int get_id();
        void set_id(unsigned int val);
        string get_name();
        void set_name(string val);
        string get_description();
        void set_description(string val);
        string get_login_url();
        void set_login_url(string val);
        string get_email();
        void set_email(string val);
        string get_username();
        void set_username(string val);
        string get_password();
        void set_password(string val);
        string get_password_hint();
        void set_password_hint(string val);
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

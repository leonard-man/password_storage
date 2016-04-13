#ifndef DATABASELAYER_H
#define DATABASELAYER_H

#include "PasswordEntry.h"
#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


class DatabaseLayer
{
    public:
        DatabaseLayer();
        virtual ~DatabaseLayer();
        vector<PasswordEntry> get_all_password_entries();
        PasswordEntry* get_password_entry(unsigned int id);
        bool insert_password_entry(PasswordEntry &password_entry);
        PasswordEntry* change_password_entry(PasswordEntry &new_password_entry);
        bool delete_password_entry(PasswordEntry &password_entry);
    protected:
    private:
};

#endif // DATABASELAYER_H

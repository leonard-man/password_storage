#ifndef DATABASELAYER_H
#define DATABASELAYER_H

#include "PasswordEntry.h"
#include <cstdlib>
#include <sqlite3.h>
#include <log4cxx/logger.h>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::helpers;

class DatabaseLayer
{
    public:
        DatabaseLayer();
        virtual ~DatabaseLayer();
        vector<PasswordEntry*> get_all_password_entries();
        PasswordEntry* get_password_entry(unsigned int id);
        bool insert_password_entry(PasswordEntry &password_entry);
        PasswordEntry* update_password_entry(PasswordEntry &new_password_entry);
        bool delete_password_entry(PasswordEntry &password_entry);
        void set_database(sqlite3 *database);
        sqlite3* get_database();
    protected:
    private:
        sqlite3* m_database = nullptr;
        bool execute_sql_on_sqlite3db(char *sql);
        void prepare_password_entry_strings(PasswordEntry &password_entry,
                                            string &entry_name,
                                            string &entry_description,
                                            string &entry_login_url,
                                            string &entry_email,
                                            string &entry_username,
                                            string &entry_password,
                                            string &entry_password_hint);
};


#endif // DATABASELAYER_H

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
        vector<PasswordEntry> get_all_password_entries();
        PasswordEntry* get_password_entry(unsigned int id);
        bool insert_password_entry(PasswordEntry &password_entry);
        PasswordEntry* change_password_entry(PasswordEntry &new_password_entry);
        bool delete_password_entry(PasswordEntry &password_entry);
        void set_database(sqlite3 *database);
        sqlite3* get_database();
        bool execute_sql_on_sqlite3db(char *sql);
    protected:
    private:
        sqlite3* m_database = nullptr;
};

inline std::string trim(const std::string &s)
{
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

#endif // DATABASELAYER_H

#include "DatabaseLayer.h"

LoggerPtr DbLogger = Logger::getLogger("DatabaseLayer");

DatabaseLayer::DatabaseLayer()
{
    //ctor
}

DatabaseLayer::~DatabaseLayer()
{
    //dtor
}

void DatabaseLayer::set_database(sqlite3 *database)
{
    LOG4CXX_INFO(DbLogger, "set_database function");

    m_database = database;
}

sqlite3* DatabaseLayer::get_database()
{
    LOG4CXX_INFO(DbLogger, "get_database function");

    return m_database;
}

vector<PasswordEntry> DatabaseLayer::get_all_password_entries()
{
    LOG4CXX_INFO(DbLogger, "get_all_password_entries function");

    //return vector<dynamic_cast<PasswordEntry*>(nullptr)>;
}

PasswordEntry* DatabaseLayer::get_password_entry(unsigned int id)
{
    LOG4CXX_INFO(DbLogger, "get_password_entry function");

    return nullptr;
}

bool DatabaseLayer::insert_password_entry(PasswordEntry& password_entry)
{
    bool result = false;

    LOG4CXX_INFO(DbLogger, "insert_password_entry function");

    char sql[] = "INSERT INTO password (ID, name, description,login_url, email, username, password, password_hint) VALUES (2, '2', '3', '4', '5', '6', '7', '8');";

    result = execute_sql_on_sqlite3db(sql);

    return result;
}

PasswordEntry* DatabaseLayer::change_password_entry(PasswordEntry& new_password_entry)
{
    LOG4CXX_INFO(DbLogger, "change_password_entry function");

    return nullptr;
}

bool DatabaseLayer::delete_password_entry(PasswordEntry& password_entry)
{
    bool result = false;

    LOG4CXX_INFO(DbLogger, "delete_password_entry function");

    char sql[] = "DELETE FROM password WHERE ID = 2;";

    result = execute_sql_on_sqlite3db(sql);

    return result;
}

bool DatabaseLayer::execute_sql_on_sqlite3db(char *sql)
{
    char *zErrMsg = 0;
    int rc;
    bool result = false;

    rc = sqlite3_exec(get_database(), sql, nullptr, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        LOG4CXX_ERROR(DbLogger, "SQL error: " + string(zErrMsg));

        sqlite3_free(zErrMsg);
        result = true;
    }
    else
    {
        LOG4CXX_INFO(DbLogger, "execute_sql_on_sqlite3db - success for: " + string(sql));
    }

    return result;
}

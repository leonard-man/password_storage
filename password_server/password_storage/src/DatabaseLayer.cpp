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
    m_database = database;
}

sqlite3* DatabaseLayer::get_database()
{
    return m_database;
}

vector<PasswordEntry> DatabaseLayer::get_all_password_entries()
{
    //return vector<dynamic_cast<PasswordEntry*>(nullptr)>;
}

PasswordEntry* DatabaseLayer::get_password_entry(unsigned int id)
{
    return nullptr;
}

bool DatabaseLayer::insert_password_entry(PasswordEntry& password_entry)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;
    bool result = false;

    // for testing purposes, only - modify to accept PasswordEntry data
    sql = "INSERT INTO password (ID, name, description,login_url, email, username, password, password_hint) VALUES (2, '2', '3', '4', '5', '6', '7', '8');";

    rc = sqlite3_exec(get_database(), sql, nullptr, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        LOG4CXX_ERROR(DbLogger, "SQL error: " + string(zErrMsg));

        sqlite3_free(zErrMsg);
        result = true;
    }
    else
    {
        LOG4CXX_INFO(DbLogger, "Records created successfully\n");
    }

    return result;
}

PasswordEntry* DatabaseLayer::change_password_entry(PasswordEntry& new_password_entry)
{
    return nullptr;
}

bool DatabaseLayer::delete_password_entry(PasswordEntry& password_entry)
{
    return false;
}

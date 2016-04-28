#include "DatabaseLayer.h"

LoggerPtr DbLogger = Logger::getLogger("DatabaseLayer");

DatabaseLayer::DatabaseLayer()
{
    //ctor
}

DatabaseLayer::~DatabaseLayer()
{
    m_database = nullptr;
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

    // TODO (sgnjidic #2 #2016-04-25): implement get_all_password_entries function

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
    char insert_cher_buffer[4000];
    int insert_string_size = 0;

    unsigned int entry_id = password_entry.get_id();
    string entry_name = password_entry.get_name();
    string entry_description = password_entry.get_description();
    string entry_login_url = password_entry.get_login_url();
    string entry_email = password_entry.get_email();
    string entry_username = password_entry.get_username();
    string entry_password = password_entry.get_password();
    string entry_password_hint = password_entry.get_password_hint();

    entry_name = trim(entry_name);
    entry_description = trim(entry_description);
    entry_login_url = trim(entry_login_url);
    entry_email = trim(entry_email);
    entry_username = trim(entry_username);
    entry_password = trim(entry_password);
    entry_password_hint = trim(entry_password_hint);

    if (entry_name.length() > 256)
    {
        entry_name = entry_name.substr(0, 255);
    }

    if (entry_description.length() > 256)
    {
        entry_description = entry_description.substr(0, 255);
    }

    if (entry_login_url.length() > 256)
    {
        entry_login_url = entry_login_url.substr(0, 255);
    }

    if (entry_email.length() > 256)
    {
        entry_email = entry_email.substr(0, 255);
    }

    if (entry_username.length() > 256)
    {
        entry_username = entry_username.substr(0, 255);
    }

    if (entry_password.length() > 256)
    {
        entry_password = entry_password.substr(0, 255);
    }

    if (entry_password_hint.length() > 256)
    {
        entry_password_hint = entry_password_hint.substr(0, 255);
    }

    LOG4CXX_INFO(DbLogger, "insert_password_entry function");

    insert_string_size =
        sprintf(
                    insert_cher_buffer,
                    "INSERT INTO password (ID, name, description,login_url, email, username, password, password_hint) VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
                    entry_id,
                    entry_name.c_str(),
                    entry_description.c_str(),
                    entry_login_url.c_str(),
                    entry_email.c_str(),
                    entry_username.c_str(),
                    entry_password.c_str(),
                    entry_password_hint.c_str()
                    );

    result = execute_sql_on_sqlite3db(insert_cher_buffer);

    return result;
}

PasswordEntry* DatabaseLayer::change_password_entry(PasswordEntry& new_password_entry)
{
    // TODO (sgnjidic #2 #2016-04-25): implement change_password_entry function

    LOG4CXX_INFO(DbLogger, "change_password_entry function");

    return nullptr;
}

bool DatabaseLayer::delete_password_entry(PasswordEntry& password_entry)
{
    bool result = false;

    // TODO (sgnjidic #2 #2016-04-25): modify delete_password_entry function to work with PasswordEntry& password_entry

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

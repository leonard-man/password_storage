#include "DatabaseLayer.h"

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
    PasswordEntry* result = nullptr;
    char select_char_buffer[150];
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";

    LOG4CXX_INFO(DbLogger, "get_password_entry function for id: " + to_string(id));

    sprintf(
            select_char_buffer,
            "select ID, name, description,login_url, email, username, password, password_hint from password where ID = %d;",
            id
           );

    rc = sqlite3_exec(get_database(), select_char_buffer, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        LOG4CXX_ERROR(DbLogger, "SQL error: " + string(zErrMsg));

        sqlite3_free(zErrMsg);
    }
    else
    {
        LOG4CXX_INFO(DbLogger, "get_password_entry - success for: " + string(select_char_buffer));
    }

    return result;
}

int DatabaseLayer::callback(void *data, int argc, char **argv, char **azColName)
{
    int i;

    LOG4CXX_ERROR(DbLogger, "SQL callback function error: " + string(data));

    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    return 0;
}

bool DatabaseLayer::insert_password_entry(PasswordEntry& password_entry)
{
    bool result = false;
    char insert_char_buffer[2000];

    LOG4CXX_INFO(DbLogger, "insert_password_entry function");

    unsigned int entry_id = password_entry.get_id();

    string entry_name;
    string entry_description;
    string entry_login_url;
    string entry_email;
    string entry_username;
    string entry_password;
    string entry_password_hint;

    prepare_password_entry_strings(password_entry,
                                   entry_name,
                                   entry_description,
                                   entry_login_url,
                                   entry_email,
                                   entry_username,
                                   entry_password,
                                   entry_password_hint);

    sprintf(
            insert_char_buffer,
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

    result = execute_sql_on_sqlite3db(insert_char_buffer);

    return result;
}

PasswordEntry* DatabaseLayer::update_password_entry(PasswordEntry& new_password_entry)
{
    char update_char_buffer[2000];
    PasswordEntry* old_password_entry;

    LOG4CXX_INFO(DbLogger, "change_password_entry function");

    unsigned int entry_id = new_password_entry.get_id();

    string entry_name;
    string entry_description;
    string entry_login_url;
    string entry_email;
    string entry_username;
    string entry_password;
    string entry_password_hint;

    prepare_password_entry_strings(new_password_entry,
                                   entry_name,
                                   entry_description,
                                   entry_login_url,
                                   entry_email,
                                   entry_username,
                                   entry_password,
                                   entry_password_hint);

    sprintf(
            update_char_buffer,
            "UPDATE password SET name = '%s', description = '%s', login_url = '%s', email = '%s', username = '%s', password = '%s', password_hint = '%s WHERE ID = %d;",
            entry_name.c_str(),
            entry_description.c_str(),
            entry_login_url.c_str(),
            entry_email.c_str(),
            entry_username.c_str(),
            entry_password.c_str(),
            entry_password_hint.c_str(),
            entry_id
           );

    // TODO (sgnjidic #2 #2016-04-28): finish change_password_entry function by returning old_password_entry to caller
    old_password_entry = get_password_entry(entry_id);

    execute_sql_on_sqlite3db(update_char_buffer);

    return old_password_entry;
}

bool DatabaseLayer::delete_password_entry(PasswordEntry& password_entry)
{
    bool result = false;
    char delete_char_buffer[50];

    LOG4CXX_INFO(DbLogger, "delete_password_entry function");

    unsigned int entry_id = password_entry.get_id();

    sprintf(
            delete_char_buffer,
            "DELETE FROM password WHERE ID = %d;",
            entry_id
            );

    result = execute_sql_on_sqlite3db(delete_char_buffer);

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
    }
    else
    {
        LOG4CXX_INFO(DbLogger, "execute_sql_on_sqlite3db - success for: " + string(sql));
        result = true;
    }

    return result;
}

void DatabaseLayer::prepare_password_entry_strings(PasswordEntry &password_entry,
                                    string &entry_name,
                                    string &entry_description,
                                    string &entry_login_url,
                                    string &entry_email,
                                    string &entry_username,
                                    string &entry_password,
                                    string &entry_password_hint)
{
    LOG4CXX_INFO(DbLogger, "prepare_password_entry_strings function");

    entry_name = password_entry.get_name();
    entry_description = password_entry.get_description();
    entry_login_url = password_entry.get_login_url();
    entry_email = password_entry.get_email();
    entry_username = password_entry.get_username();
    entry_password = password_entry.get_password();
    entry_password_hint = password_entry.get_password_hint();

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
}

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

inline std::string trim(const std::string &s)
{
    LOG4CXX_INFO(DbLogger, "trim function");

    auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
    auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
    return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
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

vector<PasswordEntry*> DatabaseLayer::get_all_password_entries()
{
    vector<PasswordEntry*> result;
    char select_char_buffer[150];
    const char *zErrMsg = 0;
    int rc;
    sqlite3_stmt* data = nullptr;

    LOG4CXX_INFO(DbLogger, "get_all_password_entries function");

    sprintf(
            select_char_buffer,
            "select ID, name, description,login_url, email, username, password, password_hint from password;"
           );

    rc = sqlite3_prepare(get_database(), (const char*) select_char_buffer, -1, &data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        LOG4CXX_ERROR(DbLogger, "SQL error: " + string(zErrMsg));
    }
    else
    {
        // TODO (developer_1 #9 #2016-05-13): handle the case when select statement in get_all_password_entries returns no rows in dataset

        int sql_row = 0;

        while(true)
        {
            sql_row = sqlite3_step(data);

            if(sql_row == SQLITE_ROW)
            {
                PasswordEntry* password_entry = new PasswordEntry();

                password_entry->set_id(sqlite3_column_int( data, 0)) ;
                password_entry->set_name((const char *)sqlite3_column_text( data, 1)) ;
                password_entry->set_description((const char *)sqlite3_column_text( data, 2)) ;
                password_entry->set_login_url((const char *)sqlite3_column_text( data, 3)) ;
                password_entry->set_email((const char *)sqlite3_column_text( data, 4)) ;
                password_entry->set_username((const char *)sqlite3_column_text( data, 5)) ;
                password_entry->set_password((const char *)sqlite3_column_text( data, 6)) ;
                password_entry->set_password_hint((const char *)sqlite3_column_text( data, 7)) ;

                result.push_back(password_entry);
            }
            else
            {
                break;
            }
        }

        sqlite3_finalize(data);

        LOG4CXX_INFO(DbLogger, "get_all_password_entries - success for: " + string(select_char_buffer));
    }

    return result;
}

PasswordEntry* DatabaseLayer::get_password_entry(unsigned int id)
{
    PasswordEntry* result = nullptr;
    char select_char_buffer[150];
    const char *zErrMsg = 0;
    int rc;
    sqlite3_stmt* data = nullptr;

    LOG4CXX_INFO(DbLogger, "get_password_entry function for id: " + to_string(id));

    sprintf(
            select_char_buffer,
            "select ID, name, description,login_url, email, username, password, password_hint from password where ID = %d;",
            id
           );

    rc = sqlite3_prepare(get_database(), (const char*) select_char_buffer, -1, &data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        LOG4CXX_ERROR(DbLogger, "SQL error: " + string(zErrMsg));

        return nullptr;
    }
    else
    {
        sqlite3_step(data);

        // TODO (developer_1 #9 #2016-05-12): handle the case when select statement in get_password_entry returns no rows in dataset

        result = new PasswordEntry();

        result->set_id(sqlite3_column_int( data, 0)) ;
        result->set_name((const char *)sqlite3_column_text( data, 1)) ;
        result->set_description((const char *)sqlite3_column_text( data, 2)) ;
        result->set_login_url((const char *)sqlite3_column_text( data, 3)) ;
        result->set_email((const char *)sqlite3_column_text( data, 4)) ;
        result->set_username((const char *)sqlite3_column_text( data, 5)) ;
        result->set_password((const char *)sqlite3_column_text( data, 6)) ;
        result->set_password_hint((const char *)sqlite3_column_text( data, 7)) ;

        sqlite3_finalize(data);

        LOG4CXX_INFO(DbLogger, "get_password_entry - success for: " + string(select_char_buffer));
    }

    return result;
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
            "UPDATE password SET name = '%s', description = '%s', login_url = '%s', email = '%s', username = '%s', password = '%s', password_hint = '%s' WHERE ID = %d;",
            entry_name.c_str(),
            entry_description.c_str(),
            entry_login_url.c_str(),
            entry_email.c_str(),
            entry_username.c_str(),
            entry_password.c_str(),
            entry_password_hint.c_str(),
            entry_id
           );

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

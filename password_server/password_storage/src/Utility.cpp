#include "Utility.h"

LoggerPtr UtilityLogger = Logger::getLogger("Utility");

Utility::Utility()
{
    //ctor
}

Utility::~Utility()
{
    sqlite3_close(m_database);
}

string Utility::get_config_path()
{
    if (root_path.empty())
    {
        read_configuration();
    }
    return root_path;
}

sqlite3* Utility::get_database_instance()
{
    int rc;

    if (root_path.empty())
    {
        read_configuration();
    }

    string sqlite_full_filename = root_path + "password_storage.sql3";

    LOG4CXX_INFO(UtilityLogger, "opening sqlite database: " + sqlite_full_filename);

    rc = sqlite3_open(sqlite_full_filename.c_str() , &m_database);

    if( rc ){
        size_t string_length = sizeof(sqlite3_errmsg(m_database));
        string error_string(sqlite3_errmsg(m_database), string_length);

        LOG4CXX_ERROR(UtilityLogger, "Can't open database: " + error_string);

        return nullptr;
    }
    else{
        LOG4CXX_DEBUG(UtilityLogger, "Opened database successfully");

        return m_database;
    }
}

bool Utility::read_configuration()
{
    Config cfg;

    try
    {
        cfg.readFile("password_storage_server_configuration.cfg");
    }
    catch(const FileIOException &fioex)
    {
        // at this point log4cxx is not initialized, as config file has not been read
        LOG4CXX_ERROR(UtilityLogger, "I/O error while reading file.");

        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
        string error_file(pex.getFile(), sizeof(pex.getFile()));
        string error_line(pex.getLine(), sizeof(pex.getLine()));
        string error_description(pex.getError(), sizeof(pex.getError()));

        // at this point log4cxx is not initialized, as config file has not been read
        LOG4CXX_ERROR(UtilityLogger, "Parse error at file: " + error_file + " line: " + error_line + " description: " + error_description);

        return(EXIT_FAILURE);
    }

    try
    {
        string name = cfg.lookup("root_path");
        // at this point log4cxx is not initialized, as config file has not been read
        LOG4CXX_INFO(UtilityLogger, "root_path: " + name);

        root_path = name;
    }
    catch(const SettingNotFoundException &nfex)
    {
        // at this point log4cxx is not initialized, as config file has not been read
        LOG4CXX_ERROR(UtilityLogger, "No 'root_path' setting in configuration file.");

        return(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

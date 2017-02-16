#include "utility.h"

LoggerPtr UtilityLogger = Logger::getLogger("Utility");

utility::utility()
{
    //ctor
}

utility::~utility()
{
    //desctuctor
}

string utility::get_config_path()
{
    if (root_path.empty())
    {
        read_configuration();
    }
    return root_path;
}

sqlite3* utility::get_database_instance()
{
    return nullptr;
}

bool utility::read_configuration()
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

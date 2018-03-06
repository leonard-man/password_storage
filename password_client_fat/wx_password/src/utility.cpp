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

string utility::get_server_ip()
{
    if (server_ip_v4.empty())
    {
        read_configuration();
    }
    return server_ip_v4;
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
        cfg.readFile("password_storage_fat_client_configuration.cfg");
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

        string server_ip = cfg.lookup("server_ip_v4");
        LOG4CXX_INFO(UtilityLogger, "server_ip_v4: " + server_ip);
        server_ip_v4 = server_ip;

    }
    catch(const SettingNotFoundException &nfex)
    {
        // at this point log4cxx is not initialized, as config file has not been read
        LOG4CXX_ERROR(UtilityLogger, "Error reading configuration file.");

        return(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

bool utility::read_message(string message)
{
    // TODO (developer_1 #3 #2018-01-07): parse xml using tinyxml
    XMLDocument* xml_doc = new XMLDocument();
    xml_doc->Parse(message.c_str());

    return false;
}

bool utility::parse_xml_string()
{

    return false;
}

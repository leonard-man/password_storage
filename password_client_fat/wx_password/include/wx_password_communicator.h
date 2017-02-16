#ifndef WX_PASSWORD_COMMUNICATOR_H
#define WX_PASSWORD_COMMUNICATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 1000000 // max number of bytes we can get at once

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class wx_password_communicator
{
    public:
        wx_password_communicator();
        virtual ~wx_password_communicator();
        string get_password_entries();
        string add_password_entry();
        string delete_password_entry();
        string edit_password_entry();
        void set_server_ipv4_address(string address);
        void init_comm();
    protected:
    private:
        string send_to_server(string message);
        in_addr* get_in_addr(struct sockaddr *sa);
        string server_ipv4_address;
};

#endif // WX_PASSWORD_COMMUNICATOR_H

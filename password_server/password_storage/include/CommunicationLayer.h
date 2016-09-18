#ifndef COMMUNICATIONLAYER_H
#define COMMUNICATIONLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/* object for socket communication - do research on interface and communication protocol <XML ans candidate?> */
class CommunicationLayer
{
    public:
        CommunicationLayer();
        virtual ~CommunicationLayer();
        void sigchld_handler(int s);
        void *get_in_addr(struct sockaddr *sa);
        int start_server();
    protected:
    private:
};

#endif // COMMUNICATIONLAYER_H

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

#include "SendPackage.h"
#include "ReceivePackage.h"
#include "Controller.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold


using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/* object for socket communication - do research on interface and communication protocol <XML ans candidate?> */
class CommunicationLayer
{
    public:
        // constructor and destructor
        CommunicationLayer();
        virtual ~CommunicationLayer();
        // functions
        int start_server();
        void set_controller(Controller* ctrl);
        Controller* get_controller();
        bool set_send_package(SendPackage* new_send_package);
    protected:
    private:
        // fields
        ReceivePackage* receive_package = nullptr;
        SendPackage* send_package = nullptr;
        Controller* controller = nullptr;
        // functions
        void process_received_package();
        void *sigchld_handler(int s);
        void *get_in_addr(struct sockaddr *sa);
        ReceivePackage* create_receive_package();
        bool remove_receive_package();
        bool remove_send_package();
};

#endif // COMMUNICATIONLAYER_H

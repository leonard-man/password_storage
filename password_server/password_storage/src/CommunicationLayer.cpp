#include "CommunicationLayer.h"

LoggerPtr CommLogger = Logger::getLogger("CommunicationLayer");

CommunicationLayer::CommunicationLayer()
{
    //ctor
}

CommunicationLayer::~CommunicationLayer()
{
    if(receive_package != nullptr)
    {
        delete receive_package;
    }

    if(send_package != nullptr)
    {
        delete send_package;
    }

    if(controller != nullptr)
    {
        delete controller;
    }

    LOG4CXX_INFO(CommLogger, "Communication layer destructor end.");

}

void CommunicationLayer::set_controller(Controller* ctrl)
{
    controller = ctrl;
    LOG4CXX_INFO(CommLogger, "Controller set.");
}

Controller* CommunicationLayer::get_controller()
{
    return controller;
}

bool CommunicationLayer::remove_receive_package()
{
    if(receive_package != nullptr)
    {
        delete receive_package;
    }

    receive_package = nullptr;

    LOG4CXX_INFO(CommLogger, "Clearing receive package.");

    return true;
}

bool CommunicationLayer::set_send_package(SendPackage* new_send_package)
{
    remove_send_package();

    send_package = new_send_package;

    LOG4CXX_INFO(CommLogger, "New send package created: " + new_send_package->get_payload());

    return true;
}

bool CommunicationLayer::remove_send_package()
{
    if(send_package != nullptr)
    {
        delete send_package;
    }

    send_package = nullptr;

    LOG4CXX_INFO(CommLogger, "Clearing send package.");

    return true;
}

ReceivePackage* CommunicationLayer::create_receive_package()
{
    remove_receive_package();

    receive_package = controller->create_receive_package();

    LOG4CXX_INFO(CommLogger, "Receive package created.");

    return receive_package;
}

void CommunicationLayer::process_received_package()
{
    // ... continue here ...
    // use debugger to step through and fix objects and references
    //
    if((controller != nullptr) && (receive_package != nullptr))
    {
        controller->set_received_package(receive_package);
    }
    // controller should parse received package
    controller->parse_package_received();
    // controller should interpret if any commands are received

    // based on commands, action should be taken, return package prepared

    // return package should be sent back to caller
    set_send_package(controller->get_send_package());
    this->send_package->set_is_sent(false);
}

void *CommunicationLayer::sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *CommunicationLayer::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int CommunicationLayer::start_server()
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = this->sigchld_handler(0); // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        char buf[1000000];

        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, this->get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);

        printf("server: got connection from %s\n", s);

        if (recv(new_fd, buf, 1000000, 0) == -1)
        {
            perror("receive");
        }
        else
        {
            ReceivePackage* rec_pack = this->create_receive_package();
            rec_pack->set_payload(string(buf));

            printf("server: got string from %s - %s\n", s, rec_pack->get_payload().c_str());

            LOG4CXX_INFO(CommLogger, "payload being recieved: " + rec_pack->get_payload());
            LOG4CXX_INFO(CommLogger, "payload received buffer size: " + to_string(rec_pack->get_payload_length()));

            this->process_received_package();
        }

        if ((send_package != nullptr) && (send_package->is_sent() == false))
        {
            LOG4CXX_INFO(CommLogger, "payload being sent: " + send_package->get_payload());
            LOG4CXX_INFO(CommLogger, "payload buffer size: " + to_string(send_package->get_payload_length()));

            if (send(new_fd, (send_package->get_payload()).c_str(), send_package->get_payload_length() , 0) == -1)
            {
                perror("send");
            }

            this->send_package->set_is_sent(true);
            // delete send_package;

            // send_package = nullptr;
        }
    }

    return 0;
}

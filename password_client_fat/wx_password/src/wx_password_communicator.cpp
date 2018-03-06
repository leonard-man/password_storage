#include "wx_password_communicator.h"

LoggerPtr DbLogger = Logger::getLogger("wx_password_communicator");

// get sockaddr  IPv4
in_addr* wx_password_communicator::get_in_addr(struct sockaddr *sa)
{
    LOG4CXX_INFO(DbLogger, "entered function get_in_addr(struct sockaddr *sa)");

    return &(((struct sockaddr_in*)sa)->sin_addr);
}

wx_password_communicator::wx_password_communicator()
{
    //ctor
}

wx_password_communicator::~wx_password_communicator()
{
    delete(this->utils);
    this->utils = nullptr;
}

void wx_password_communicator::set_utility(utility* utils)
{
    this->utils = utils;
}

string wx_password_communicator::get_password_entries()
{
    LOG4CXX_INFO(DbLogger, "entered function get_password_entries()");

    return nullptr;
}

string wx_password_communicator::add_password_entry()
{
    LOG4CXX_INFO(DbLogger, "entered function add_password_entry()");

    return nullptr;
}

string wx_password_communicator::delete_password_entry()
{
    LOG4CXX_INFO(DbLogger, "entered function delete_password_entry()");

    return nullptr;
}

string wx_password_communicator::edit_password_entry()
{
    LOG4CXX_INFO(DbLogger, "entered function edit_password_entry()");

    return nullptr;
}

string wx_password_communicator::send_to_server(string message)
{
    return nullptr;
}

void wx_password_communicator::set_server_ipv4_address(string address)
{
    LOG4CXX_INFO(DbLogger, "entered function set_server_ipv4_address()");

    server_ipv4_address = address;
}

void wx_password_communicator::init_comm()
{
    int sockfd;
    int numbytes;
    char buf[MAXDATASIZE];
    string payload;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    LOG4CXX_INFO(DbLogger, "entered function init_comm()");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(server_ipv4_address.c_str(), PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        LOG4CXX_INFO(DbLogger, "error getting password_storage server address info: " + string(gai_strerror(rv)));
        return;
    }
    else
    {
        LOG4CXX_INFO(DbLogger, "connecting to password_storage server at: " + server_ipv4_address);
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        LOG4CXX_INFO(DbLogger, "client - failed to connect to password_storage server at: " + server_ipv4_address);

        return;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);

    printf("client: connecting to %s\n", s);
    LOG4CXX_INFO(DbLogger, "client - connecting to password_storage server at: " + server_ipv4_address);

    freeaddrinfo(servinfo); // all done with this structure

    payload = "<list_all_passwords>";

    if (send(sockfd, payload.c_str(), payload.length(), 0) == -1)
        perror("send");

    LOG4CXX_INFO(DbLogger, "client - sent to password_storage server: " + payload);

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n", buf);

    payload = string(buf);

    LOG4CXX_INFO(DbLogger, "client - received from password_storage server: " + payload);

    utils->read_message(payload);

    close(sockfd);

    return;
}

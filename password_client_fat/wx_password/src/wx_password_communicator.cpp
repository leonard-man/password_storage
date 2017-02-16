#include "wx_password_communicator.h"

// get sockaddr  IPv4
in_addr* wx_password_communicator::get_in_addr(struct sockaddr *sa)
{
    return &(((struct sockaddr_in*)sa)->sin_addr);
}

wx_password_communicator::wx_password_communicator()
{
    //ctor
}

wx_password_communicator::~wx_password_communicator()
{
    //dtor
}

string wx_password_communicator::get_password_entries()
{
    return nullptr;
}

string wx_password_communicator::add_password_entry()
{
    return nullptr;
}

string wx_password_communicator::delete_password_entry()
{
    return nullptr;
}

string wx_password_communicator::edit_password_entry()
{
    return nullptr;
}

void wx_password_communicator::set_server_ipv4_address(string address)
{
    server_ipv4_address = address;
}

int wx_password_communicator::init_comm()
{
    int sockfd;
    int numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(server_ipv4_address.c_str(), PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n", buf);

    if (send(sockfd, "Client: little data back...", 28, 0) == -1)
        perror("send");

    close(sockfd);

    return 0;
}

string wx_password_communicator::send_to_server(string message)
{
    return nullptr;
}

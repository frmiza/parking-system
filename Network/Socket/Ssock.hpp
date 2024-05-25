#ifndef SSOCK_HPP
#define SSOCK_HPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKETERROR (-1)

namespace SW
{
    class Ssock
    {
    private:
        struct sockaddr_in addr;
        int s_sock;
        
    public:
        //Constutor
        Ssock(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        // Interface p/ connet ou bind 
        virtual void connection_network(int s_sock, struct sockaddr_in addr) = 0;

        void check(int expression);
        
        //Gets
        struct sockaddr_in get_addr();
        int get_s_sock();
        
        //Sets
        void set_port(int port);
        void set_ip(const std::string& ip);
        void set_ip(int ip_adderss);
    };
}

#endif //SSOCK_HPP

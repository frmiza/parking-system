#ifndef CONNECTSOCK_HPP
#define CONNECTSOCK_HPP

#include "Ssock.hpp"

namespace SW
{
    class ConnectSock: public Ssock
    {
    private:
    
        int connecting;
        // Implementacao da abstracao da connect
        void connection_network(int s_sock, struct sockaddr_in addr) override;
    public:

        // Construtor
        ConnectSock(u_short port_to_connect, std::string ip_address_to_connect,
            int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        //Gets
        int get_connecting();
    };
}

#endif //CONNECTSOCK_HPP
#ifndef BINDSOCK_HPP
#define BINDSOCK_HPP

#include "Ssock.hpp"

namespace SW
{
    class BindSock: public Ssock
    {
    private:
        int binding;

        // Implementacao da abstracao da bind
        void connection_network(int s_sock, struct sockaddr_in addr) override;

    public:
        // Construtor
        BindSock(u_int port, u_long ip_address = INADDR_ANY,
            int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        // Gets
        int get_binding();
    };

}

#endif //BINDSOCK_GPP
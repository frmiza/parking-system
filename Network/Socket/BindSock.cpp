#include "BindSock.hpp"

// Construtor
SW::BindSock::BindSock(u_int port, u_long ip_address, int domain, 
            int type, int protocol) : Ssock(domain, type, protocol)
{   
    set_port(port);

    connection_network(get_s_sock(), get_addr());
    check(binding);
}

// Implementacao da abstracao da bind
void SW::BindSock::connection_network(int s_sock, sockaddr_in addr)
{
    binding = bind(s_sock, (struct sockaddr *)&addr, sizeof(addr));
}


// Gets

int SW::BindSock::get_binding(){
    return binding;
}
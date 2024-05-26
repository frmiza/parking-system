#include "ConnectSock.hpp"

// Construtor
SW::ConnectSock::ConnectSock(u_short port_to_connect, std::string ip_address_to_connect, int domain,
             int type, int protocol) : Ssock(domain, type, protocol)
{ 
    set_ip(ip_address_to_connect);
    set_port(port_to_connect);

    connection_network(get_s_sock(), get_addr());
    check(connecting);
}

// Implementacao da abstracao da connect
void SW::ConnectSock::connection_network(int s_sock, sockaddr_in addr)
{
    connecting = connect(s_sock, (struct sockaddr *)&addr, sizeof(addr));
}

// Gets
int SW::ConnectSock::get_connecting()
{
    return connecting;
}
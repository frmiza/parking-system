#include "Client.hpp"

SW::Client::Client(u_int port_to_connect, const char* ip_address_to_connect,
                    int domain, int type, int protocol)
{
    socket = new ConnectSock(port_to_connect, ip_address_to_connect, domain, type, protocol);
}

SW::ConnectSock* SW::Client::get_socket()
{
    return socket;
}
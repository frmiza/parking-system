#include "Server.hpp"

SW::Server::Server(int backlog, u_int port, u_long ip_address, int domain, 
                int type, int protocol)
{
    socket = new ListenSock(backlog, port, ip_address, domain, type, protocol);
}

SW::ListenSock* SW::Server::get_socket()
{
    return socket;
}
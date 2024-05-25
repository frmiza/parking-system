#include "ListenSock.hpp"

// Construtor
SW::ListenSock::ListenSock(int backlog, u_int port, u_long ip_address, int domain, 
                int type, int protocol) : BindSock(port, ip_address, domain, type, protocol)
{
    s_backlog = backlog;
    start_listen();
    check(listening);
}   

// Listen
void SW::ListenSock::start_listen()
{
    listening = listen(get_s_sock(), s_backlog);
}


// Gets
int SW::ListenSock::get_s_backlog()
{
    return s_backlog;
}

int SW::ListenSock::get_listening()
{
    return listening;
}
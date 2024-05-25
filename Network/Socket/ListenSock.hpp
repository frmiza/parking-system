#ifndef LISTENSOCK_HPP
#define LISTENSOCK_HPP

#include "BindSock.hpp"

namespace SW
{
    class ListenSock: public BindSock
    {
    private:
        int s_backlog;
        int listening;
    public:
        // Construtor
        ListenSock(int backlog, u_int port, u_long ip_address = INADDR_ANY,
            int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        //Listen func
        void start_listen();

        // Gets
        int get_s_backlog();
        int get_listening();

    };

}

#endif //CONNECTSOCK_HPP
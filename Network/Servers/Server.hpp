#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Socket/SwLibSocks.hpp"


namespace SW
{
    class Server
    {       
    private:
        ListenSock* socket;
        // Implementa o comportamento do servidor ou client instanciado
        virtual void accepter() = 0;
        virtual void handler_con(int c_sock) = 0 ;
        //virtual void responser_con() = 0;

    public:
        // ConstrutorS
        Server(int backlog, u_int port, u_long ip_address = INADDR_ANY,
            int domain = AF_INET, int  type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        virtual void launch() = 0;

        // Gets
        ListenSock* get_socket();
    };
}
#endif // SERVER_HPP
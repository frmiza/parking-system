#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../SwLibNet.hpp"


namespace SW
{
    class Client
    {       
    private:
        ConnectSock* socket;
        // Implementa o comportamento do servidor ou client instanciado
        virtual void connecter() = 0;
        virtual void handler_con(int s_sock) = 0 ;
        //virtual void responser_con() = 0;

    public:
        // Construtor
        Client(u_int port_to_connect, const char* ip_address_to_connect, int domain = AF_INET,
                int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        virtual void launch() = 0;

        // Gets
        ConnectSock* get_socket();
    };
}
#endif // SERVER_HPP
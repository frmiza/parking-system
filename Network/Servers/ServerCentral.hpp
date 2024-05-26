#ifndef SERVERCENTRAL_HPP
#define SERVERCENTRAL_HPP

#include "Server.hpp"
#include "../../Json/JsonHdrLib.hpp"


namespace SW
{
    class ServerCentral : public Server
    {
    private:
        // Array com as threads
        //std::vector<std::thread> threads;
        
        // Socket do cliente a ser aceito.
        int cli_sock; 
    
        virtual void accepter()  override;
        virtual void handler_con(int c_sock) override;
    public:
        ServerCentral(int backlog, u_int port, u_long ip_address = INADDR_ANY,
            int domain = AF_INET, int  type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        static void* handler_con_static(void* p_client);
        void launch();
    };
}

#endif // SERVERCENTRAL_HPP
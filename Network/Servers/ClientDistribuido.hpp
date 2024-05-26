#ifndef CLIENTDISTRIBUIDO_HPP
#define CLIENTDISTRIBUIDO_HPP

#include <unistd.h>
#include "Client.hpp"
#include "../../Json/JsonHdrLib.hpp"
#include "../../Shared/shared.hpp"

namespace SW
{
    class ClientDistribuido : public Client
    {
    private:       
        // Socket do cliente aceito.
        int svr_sock; 
        struct shared_data_client& c_shared_data;
        std::mutex& c_data_mutex;

        virtual void connecter() override;
        virtual void handler_con(int s_sock) override;
        
    public:
        ClientDistribuido(struct shared_data_client sdc, std::mutex& mutex_floor, u_int port_to_connect, std::string ip_address_to_connect, int domain = AF_INET,
                int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
        void launch();
    };
}

#endif // CLIENTDISTRIBUIDO_HPP
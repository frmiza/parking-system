#ifndef CLIENTDISTRIBUIDO_HPP
#define CLIENTDISTRIBUIDO_HPP

#include "Client.hpp"

namespace SW
{
    class ClientDistribuido : public Client
    {
    private:       
        // Socket do cliente aceito.
        int svr_sock; 
    
        virtual void connecter() override;
        virtual void handler_con(int s_sock) override;
        //virtual void responser_con() = 0;
    public:
        ClientDistribuido();
        void launch();
    };
}

#endif // CLIENTDISTRIBUIDO_HPP
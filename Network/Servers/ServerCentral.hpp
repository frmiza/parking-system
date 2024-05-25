#ifndef SERVERCENTRAL_HPP
#define SERVERCENTRAL_HPP

#include "Server.hpp"
#include <vector>
#include <thread>

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
        //virtual void responser_con() = 0;
    public:
        ServerCentral();
        void launch();
    };
}

#endif // SERVERCENTRAL_HPP
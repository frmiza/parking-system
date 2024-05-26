#include "ServerCentral.hpp"
#include "../../Shared/shared.hpp"
#include "../../Shared/env.hpp"
#include <thread>
#include <unistd.h>

SW::ServerCentral::ServerCentral(int backlog, u_int port, u_long ip_address,
            int domain, int type, int protocol) : 
            Server(backlog, port, ip_address, domain, type, protocol)
{
    launch();
}

void SW::ServerCentral::accepter(){

    struct sockaddr_in address = get_socket()->get_addr();
    int addrlen = sizeof(address);
    
    try
    {   
        while(true)
        {   
            std::cout << "Aguardando dados..." << std::endl;
            cli_sock = accept(get_socket()->get_s_sock(), (sockaddr *)&address, (socklen_t *)&addrlen);
            get_socket()->check(cli_sock);
            handler_con(cli_sock);      
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
    
void SW::ServerCentral::handler_con(int c_sock){

    size_t lenmsg;
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    if((lenmsg = recv(c_sock,buffer,4096,0)) <= 0){
        close(c_sock);
        exit(EXIT_FAILURE);
    }
    
    JHR::JsonData* json_bh = new JHR::JsonData();
    json_bh->treat_json_buffer(buffer);
    //std::cout << json_bh->get_data_server() << std::endl; 

    {
        std::lock_guard<std::mutex> lock(data_mutex_server);
        JHR::JsonData* json_fh = new JHR::JsonData();
        json_fh->read_json_file(SERVER_DATA_CLIENT_JSON);      
        json_fh->modify_json_data(json_fh->get_data_server(),json_bh->get_data_server(),json_bh->get_origin());
        json_fh->save_json_file(SERVER_DATA_CLIENT_JSON);
        delete json_fh;
    }

    delete json_bh;

    close(c_sock);  // Fechar o socket após o processamento 

    return;
}

void SW::ServerCentral::launch() {
        // Chama accepter() para lidar com conexões
        accepter();
    }


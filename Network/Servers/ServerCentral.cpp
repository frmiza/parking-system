#include "ServerCentral.hpp"
#include <unistd.h>

using json = nlohmann::json;


SW::ServerCentral::ServerCentral() : Server(5,4001,INADDR_ANY, AF_INET, SOCK_STREAM,IPPROTO_TCP)
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
            std::cout << "Aguardando nova conexao..." << std::endl;
            cli_sock = accept(get_socket()->get_s_sock(), (sockaddr *)&address, (socklen_t *)&addrlen);
            get_socket()->check(cli_sock);
            handler_con(cli_sock);

            //Cria thread para tratar a request
            //threads.push_back(std::thread(&ServerCentral::handler_con, this, cli_sock));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SW::ServerCentral::handler_con(int c_sock){
    char buffer[1024] = {0};
    int valread = recv(c_sock, buffer, 1024,0);
    std::cout << "Received: " << buffer << std::endl;
        
    json j = {
        {"nome", "João"},
        {"idade", 30},
        {"solteiro", true}
    };

    std::string json_string = j.dump();
    // Exemplo de resposta
    //const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    send(c_sock, json_string.c_str(), json_string.length(), 0);

    close(c_sock);  // Fechar o socket após o processamento

    return;
}

void SW::ServerCentral::launch() {
        // Chama accepter() para lidar com conexões
        accepter();
    }


#include "ClientDistribuido.hpp"
#include <unistd.h>
#define ip_serv "127.0.0.1"


using json = nlohmann::json;


SW::ClientDistribuido::ClientDistribuido() : Client(4001,ip_serv, AF_INET, SOCK_STREAM,IPPROTO_TCP)
{   
    std::cout << "Iniciando Cliente..." << std::endl;
    launch();
}

void SW::ClientDistribuido::connecter(){

    int s_sock = get_socket()->get_s_sock();
    //struct sockaddr_in address = get_socket()->get_addr();
    //int addrlen = sizeof(address);
      
    try
    {   
        std::cout << "Se conectando ao servidor..." << std::endl;
        //svr_sock = connect(get_socket()->get_s_sock(), (sockaddr *)&address, sizeof(address));
        //get_socket()->check(svr_sock);
        handler_con(s_sock);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SW::ClientDistribuido::handler_con(int svr_sock){

    std::cout << "Aguardando dados do servidor...\n" << std::endl;
    
    const char* msg = "Ola servidor, mensagem do cliente...\n";
    if(send(svr_sock, msg, strlen(msg),0) != strlen(msg)){
        std::cout << (stderr, "Erro ao enviar mensagem: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    size_t lenmsg;
    char buffer[4096] = {0};
    memset(buffer, 0, sizeof(buffer));
    if((lenmsg = recv(svr_sock,buffer,4096,0)) <= 0){
        std::cout << "Erro ao recever mensagem mensagem" << std::endl;
    exit(EXIT_FAILURE);
    }
    //std::cout << "Received: " << buffer << std::endl;
    
    json received_json;
    try 
    {
        received_json = json::parse(buffer);
    } catch (const std::exception& e) {
        std::cerr << "erro ao analisar o json recebido: " << e.what() << std::endl;
    }
    std::cout << "JSON recebido:\n" << received_json.dump(4) << std::endl;

    //json j = {
    //    {"nome", "João"},
    //    {"idade", 30},
    //    {"solteiro", true}
    //};

    //std::string json_string = j.dump();
    // Exemplo de resposta
    //const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    //send(svr_sock, json_string.c_str(), json_string.length(), 0);

    close(svr_sock);  // Fechar o socket após o processamento
    return;
}

void SW::ClientDistribuido::launch() {
        // Chama accepter() para lidar com conexões
        connecter();
}

#include "Ssock.hpp"

// Construtor padrao
SW::Ssock::Ssock(int domain, int type, int protocol)
{

    //Define socket  
    s_sock = socket(domain, type, protocol);
    check(s_sock);

    memset(&addr,0,sizeof(addr));
    addr.sin_family = domain;
}   

// Testa expressao de conexao
void SW::Ssock::check(int expression)
{
    if(expression == SOCKETERROR){
        perror("Falha ao conectar");
        exit(EXIT_FAILURE);
    }
}

// Gets
struct sockaddr_in SW::Ssock::get_addr()
{
    return addr;
}

int SW::Ssock::get_s_sock()
{
    return s_sock;
}

// Sets
void SW::Ssock::set_port(int port)
{
    addr.sin_port = htons(port);
}

void SW::Ssock::set_ip(const std::string& ip)
{
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
}

void SW::Ssock::set_ip(int ip_adderess)
{
    addr.sin_addr.s_addr = htonl(ip_adderess);
}
#include "ClientDistribuido.hpp"

SW::ClientDistribuido::ClientDistribuido(struct shared_data_client sdc, std::mutex& mutex_floor, 
                u_int port_to_connect, std::string ip_address_to_connect, int domain, int type, int protocol) : 
                Client(port_to_connect, ip_address_to_connect, domain, type, protocol),
                c_shared_data(sdc), c_data_mutex(mutex_floor)
{   
    std::cout << "Iniciando Cliente..." << std::endl;
    
    launch();
}

void SW::ClientDistribuido::connecter(){

    int s_sock = get_socket()->get_s_sock();

    try
    {   
        std::cout << "Se conectando ao servidor..." << std::endl;
        handler_con(s_sock);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SW::ClientDistribuido::handler_con(int svr_sock){
    
    json json_buffer;
    JHR::JsonData* json_bh = new JHR::JsonData;
    std::string json_string;

    {   
        std::lock_guard<std::mutex> lock(c_data_mutex);
        struct shared_data_client aux_sdc = read_shared_data_client(c_shared_data); 
        json_buffer = json_bh->json_serializer(aux_sdc.origin, aux_sdc.num_occupied, aux_sdc.park_spaces,
        aux_sdc.rs_floor_signal, aux_sdc.dw_floor_signal, aux_sdc.open_floor_signal);
        json_string = json_buffer.dump();
    }

    if(send(svr_sock, json_string.c_str(), json_string.length(), 0) != json_string.length()){
        close(svr_sock);
        exit(EXIT_FAILURE);
    }

    close(svr_sock);  // Fechar o socket após o processamento
    return;
}

void SW::ClientDistribuido::launch() {
        // Chama accepter() para lidar com conexões
        connecter();
}

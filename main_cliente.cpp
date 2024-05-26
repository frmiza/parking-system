#include <Network/SwLibNet.hpp>
#include <Json/JsonHdrLib.hpp>
#include <Shared/env.hpp>
#include <Shared/shared.hpp>
#include <EmbedSys/Floors.hpp>
#include <iostream>

using namespace std;

void start_client()
{
    JHR::JsonConfSvr* json_conf = new JHR::JsonConfSvr();
    json_conf->treat_json_file(SERVER_CONF_JSON);
    SW::ClientDistribuido* cd = new SW::ClientDistribuido(sdc_floor0, data_mutex_client_floor0, json_conf->get_svr_port(),json_conf->get_svr_ip_addr());
}

void start_rasp()
{
    floor_terreo(sdc_floor0, data_mutex_client_floor0);
}

int main(int argc, char const *argv[])
{   
    start_client();
    start_rasp();
    return 0;
}
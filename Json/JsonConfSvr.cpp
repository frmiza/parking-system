#include "JsonConfSvr.hpp"

JHR::JsonConfSvr::JsonConfSvr() :
    svr_ip_addr(""),
    svr_port(0) {}

void JHR::JsonConfSvr::json_deserializer(json json_data)
{
    json_data.at("ip_address").get_to(svr_ip_addr);
    json_data.at("port").get_to(svr_port);
    return;
}

json JHR::JsonConfSvr::json_serializer(std::string svr_ip_addr, int svr_port)
{
    json svr_conf = {
        {"ip_address", svr_ip_addr},
        {"port", svr_port}
    };
    return svr_conf;
}

// Gets
std::string JHR::JsonConfSvr::get_svr_ip_addr() const
{
    return svr_ip_addr;
}

u_int JHR::JsonConfSvr::get_svr_port() const
{
    return svr_port;
}


#ifndef JSONCONFSVR_HPP
#define JSONCONFSVR_HPP

#include "HandlerJson.hpp"

namespace JHR
{
    class JsonConfSvr : public HandlerJson
    {
    private: 
        std::string svr_ip_addr;
        int svr_port;
        virtual void json_deserializer(json json_data) override;
        json json_serializer(std::string svr_ip_server, int svr_port);

    public:

        JsonConfSvr();
        //void treat_json_file(const std::string& file_name);
        //void treat_json_buffer(char* json_buffer);

        // Gets
        std::string get_svr_ip_addr() const;
        int get_svr_port() const;

        //Sets
        void set_svr_ip_addr(std::string svr_ip);
        void set_port(int svr_port);
        
    };
} 



#endif // JSONCONFSVR_HPP
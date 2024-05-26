#pragma once
#ifndef HENDLERJSON_HPP
#define HANDLERJSON_HPP

#include <nlohmann/json.hpp>
#include <Io/FileHandler.hpp>
#include <cstring>

using json = nlohmann::json;

namespace JHR
{
    class HandlerJson
    {  
    private:
        std::string json_type;
        json data_server;

    public:
        HandlerJson();
        virtual void json_deserializer(json json_data) = 0;
        template<typename T> const char* json_serializer(T t);
        
        void json_converter(const std::string& json_buffer);
        void read_json_file(const std::string& file_name);
        void save_json_file(const std::string& file_name);
        
        void treat_json_file(const std::string& file_name);
        void treat_json_buffer(char* json_buffer);

        // Gets
        json& get_data_server();
        std::string get_json_type() const;

        // Sets
        void set_data_server(json json_data);
        void set_json_type(std::string jtype);
    };
}
#endif //HANDLERJSON_HPP
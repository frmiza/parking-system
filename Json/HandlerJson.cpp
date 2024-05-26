#include "HandlerJson.hpp"
#include <iostream>
#include <fstream>
#include <string>

JHR::HandlerJson::HandlerJson() :
    json_type(""),
    data_server(nullptr) {}

void JHR::HandlerJson::json_converter(const std::string& json_buffer)
{   
    data_server = json::parse(json_buffer);
}

void JHR::HandlerJson::read_json_file(const std::string& file_name)
{
    FH::FileHandler* fh = new FH::FileHandler();
    fh->read_file(file_name);

    if(fh->get_buffer() != nullptr){
        json_converter(std::string(fh->get_buffer(), fh->get_size()));
    }
    delete fh;
    return;
}

/*
void JHR::HandlerJson::json_converter(char* json_buffer)
{   
    data_server = json::parse(json_buffer);
}

void JHR::HandlerJson::read_json_file(const std::string& file_name)
{
    FH::FileHandler* fh = new FH::FileHandler();
    fh->read_file(file_name);


    if(fh->get_buffer() != nullptr){
        json_converter(fh->get_buffer());
    }
    delete fh;
    return;
}
*/

void JHR::HandlerJson::save_json_file(const std::string& file_name)
{
    FH::FileHandler* fh = new FH::FileHandler();
    
    std::string json_string = get_data_server().dump();
    char *buffer = new char[json_string.length() + 1];
    std::strcpy(buffer, json_string.c_str());
    
    fh->save_file(file_name,buffer);
    delete[] buffer;
    delete fh;
    return;
}

void JHR::HandlerJson::treat_json_file(const std::string& file_name)
{
    read_json_file(file_name);
    json_deserializer(get_data_server());
    return;
}

void JHR::HandlerJson::treat_json_buffer(char* json_buffer)
{
    json_converter(json_buffer);
    json_deserializer(get_data_server());
    return;
}

// Gets
json& JHR::HandlerJson::get_data_server()
{
    return data_server;
}

std::string JHR::HandlerJson::get_json_type() const
{
    return json_type;
}

// Sets
void JHR::HandlerJson::set_data_server(json json_data)
{
    data_server = json_data;
}

void JHR::HandlerJson::set_json_type(std::string jtype)
{
    json_type = jtype;
}
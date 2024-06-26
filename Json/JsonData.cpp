#include "JsonData.hpp"

JHR::JsonData::JsonData() : 
    origin(""),
    num_occupied(0),
    park_spaces({}),
    rs_floor_signal(false),
    dw_floor_signal(false), 
    open_floor_signal(false) {}

void JHR::JsonData::json_deserializer(json json_data)
{
    if (json_data.contains("Origin") && json_data.contains("Datas")) {
        origin = json_data.at("Origin").get<std::string>();
        json data = json_data.at("Datas");
        num_occupied = data.at("Occupieds").get<int>();
        park_spaces = data.at("Spaces").get<std::vector<int>>();
        rs_floor_signal = data.at("FloorRising").get<bool>();
        dw_floor_signal = data.at("FloorDown").get<bool>();
        open_floor_signal = data.at("Opened").get<bool>();
    }
    return;
}

json JHR::JsonData::json_serializer(std::string origin, int num_occupied, std::vector<int> park_spaces,
                                    bool rs_floor_signal, bool dw_floor_signal,  bool open_floor_signal)
{
    json json_data= {
        {"Origin", origin},
        {"Datas", {
            {"Occupieds", num_occupied},
            {"Spaces", park_spaces},
            {"FloorRising", rs_floor_signal},
            {"FloorDown", dw_floor_signal},
            {"Opened", open_floor_signal}
        }}
    };
    return json_data;
}

void JHR::JsonData::modify_json_data(json& json_data_file, json new_json_data, 
                                    const std::string& origin_server)
{ 
    for (auto& floor : json_data_file["floors"]) {
        if (floor["Origin"] == origin_server) {
            floor["Datas"]["Occupieds"] = new_json_data["Datas"]["Occupieds"];
            floor["Datas"]["Spaces"] = new_json_data["Datas"]["Spaces"];
            floor["Datas"]["FloorRising"] = new_json_data["Datas"]["FloorRising"];
            floor["Datas"]["FloorDown"] = new_json_data["Datas"]["FloorDown"];
            floor["Datas"]["Opened"] = new_json_data["Datas"]["Opened"];
        }
    }
    return;
}

// Get
std::string JHR::JsonData::get_origin() const
{
    return origin;
}

int JHR::JsonData::get_num_occupied() const 
{
    return num_occupied;
}

std::vector<int> JHR::JsonData::get_park_spaces() const 
{
    return park_spaces;
}

bool JHR::JsonData::get_rs_floor_signal() const 
{
    return rs_floor_signal;
}

bool JHR::JsonData::get_dw_floor_signal() const 
{
    return dw_floor_signal;
}

bool JHR::JsonData::get_open_floor_signal() const 
{
    return open_floor_signal;
}

// Sets 
void JHR::JsonData::set_open_floor_signal(bool signal) 
{
    open_floor_signal = signal;
}
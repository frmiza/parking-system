#ifndef JSONDATA_HPP
#define JSONDATA_HPP

#include "HandlerJson.hpp"
#include <vector>

namespace JHR
{
    class JsonData : public HandlerJson
    {
    private: 
        std::string origin;
        int num_occupied;
        std::vector<int> park_spaces;
        bool rs_floor_signal;
        bool dw_floor_signal;
        bool open_floor_signal;
        
    public:

        JsonData();
        void modify_json_data(json& json_data_file, json new_json_data, const std::string& origin_server);
        virtual void json_deserializer(json json_data) override;
        json json_serializer(std::string origin, int num_occupied, std::vector<int> park_spaces,
                                    bool rs_floor_signal, bool dw_floor_signal,  bool open_floor_signal);

        // Gets
        std::string get_origin() const;
        int get_num_occupied() const;
        std::vector<int> get_park_spaces() const;
        bool get_rs_floor_signal() const;
        bool get_dw_floor_signal() const;
        bool get_open_floor_signal() const;

        // Sets
        void set_open_floor_signal(bool signal);
        
    };
} 



#endif // JSONCONFSVR_HPP
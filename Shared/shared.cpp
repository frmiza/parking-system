#include "shared.hpp"

shared_data_client sdc_floor0;
shared_data_client sdc_floor1;
shared_data_client sdc_floor2;

std::unordered_map<std::string, bool> signal_led;

std::mutex data_mutex_server;
std::mutex data_mutex_client_floor0;
std::mutex data_mutex_client_floor1;
std::mutex data_mutex_client_floor2;

struct shared_data_client read_shared_data_client(struct shared_data_client sdc) 
{
    shared_data_client read_sdc;
    read_sdc.origin = sdc.origin;
    read_sdc.num_occupied = sdc.num_occupied;
    read_sdc.park_spaces = sdc.park_spaces;
    read_sdc.rs_floor_signal = sdc.rs_floor_signal;
    read_sdc.dw_floor_signal = sdc.dw_floor_signal;
    read_sdc.open_floor_signal = sdc.open_floor_signal;

    return read_sdc;
}

void write_shared_data_client(struct shared_data_client sdc, std::string origin,
    int num_occupied, std::vector<int>& park_spaces, bool rs_floor_signal, bool dw_floor_signal,
    bool open_floor_signal)  
{
    sdc.origin = origin;
    sdc.num_occupied = num_occupied;
    sdc.park_spaces = park_spaces;
    sdc.rs_floor_signal = rs_floor_signal;
    sdc.dw_floor_signal = dw_floor_signal;
    sdc.open_floor_signal = open_floor_signal;
}

bool read_signal_led(struct shared_data_client sdc)
{
    return sdc.open_floor_signal;
}

void write_signal_led(struct shared_data_client sdc, bool signal_led)
{
    sdc.open_floor_signal = signal_led;
}
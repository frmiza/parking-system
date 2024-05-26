#ifndef SHARED_H
#define SHARED_H

#include <unordered_map>
#include <mutex>
#include <vector>
#include <string>

typedef struct shared_data_client {
    std::string origin;
    int num_occupied;
    std::vector<int> park_spaces;
    bool rs_floor_signal;
    bool dw_floor_signal;
    bool open_floor_signal;
}shared_data_client;

extern shared_data_client sdc_floor0;
extern shared_data_client sdc_floor1;
extern shared_data_client sdc_floor2;

extern std::unordered_map<std::string,bool> signal_led;

extern std::mutex data_mutex_server;
extern std::mutex data_mutex_client_floor0;
extern std::mutex data_mutex_client_floor1;
extern std::mutex data_mutex_client_floor2;

struct shared_data_client read_shared_data_client(struct shared_data_client);
void write_shared_data_client(struct shared_data_client, std::string origin,
    int num_occupied, std::vector<int>& park_spaces, bool rs_floor_signal, bool dw_floor_signal,
    bool open_floor_signal);

bool read_signal_led(struct shared_data_client sdc);
void write_signal_led(struct shared_data_client sdc, bool signal_led);

#endif // SHARED_H

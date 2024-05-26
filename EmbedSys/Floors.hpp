#ifndef FLOORS_HPP
#define FLOORS_HPP

#include <mutex>
#include "../Shared/shared.hpp" 

int floor_terreo(struct shared_data_client& sdc, std::mutex& mutex_floor);

#endif // FLOORS_HPP
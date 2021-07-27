#pragma once
#include <unordered_map>

#include "vehicle_plate.h"
#include "hasher.h"

using namespace std;

class ParkingCounter
{
public:
    // зарегистрировать парковку автомобиля
    void Park(VehiclePlate car) 
    {
        // место для вашей реализации
        if (car_to_parks_.find(car) == car_to_parks_.end())
        {
            car_to_parks_.insert({ car, 1 });
        }
        else
        {
            car_to_parks_.at(car)++;
        }
    }

    // метод возвращает количество зарегистрированных 
    // парковок автомобиля
    int GetCount(const VehiclePlate& car) const
    {
        // место для вашей реализации
        if (car_to_parks_.find(car) == car_to_parks_.end())
        {
            return 0;
        }
        return  car_to_parks_.at(car);
    }

    auto& GetAllData() const 
    {
        return car_to_parks_;
    }



private:
    std::unordered_map<VehiclePlate, int, VehiclePlateHasher> car_to_parks_{};

    // для хранения данных используйте контейнер unordered_map
    // назовите поле класса car_to_parks_
};
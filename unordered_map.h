#pragma once
#include <unordered_map>

#include "vehicle_plate.h"
#include "hasher.h"

using namespace std;

class ParkingCounter
{
public:
    // ���������������� �������� ����������
    void Park(VehiclePlate car) 
    {
        // ����� ��� ����� ����������
        if (car_to_parks_.find(car) == car_to_parks_.end())
        {
            car_to_parks_.insert({ car, 1 });
        }
        else
        {
            car_to_parks_.at(car)++;
        }
    }

    // ����� ���������� ���������� ������������������ 
    // �������� ����������
    int GetCount(const VehiclePlate& car) const
    {
        // ����� ��� ����� ����������
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

    // ��� �������� ������ ����������� ��������� unordered_map
    // �������� ���� ������ car_to_parks_
};
#pragma once
#include <array>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <ctime>

#include "vehicle_plate.h"
#include "hasher.h"

using namespace std;
using namespace std::literals;
using namespace std::chrono;


// выбросьте это исключение в случае ошибки парковки
struct ParkingException 
{   
};

template <typename Clock>
class Parking 
{
    // при обращении к типу внутри шаблонного параметра мы обязаны использовать 
    // typename; чтобы этого избежать, объявим псевдонимы для нужных типов
    using Duration = typename Clock::duration;
    using TimePoint = typename Clock::time_point;
   
public:
    Parking(int cost_per_second) : cost_per_second_(cost_per_second) {}

    // запарковать машину с указанным номером
    void Park(VehiclePlate car) 
    {
        if (now_parked_.count(car) == 0)
        {
            const TimePoint start_time_ = Clock::now();
            now_parked_[car] = start_time_;
        }
        else
        {
            throw ParkingException();
        }        
    }

    // забрать машину с указанным номером
    void Withdraw(const VehiclePlate& car) 
    {
        if (now_parked_.count(car) != 0)
        {
             TimePoint end_time = Clock::now();
             Duration dur = (end_time - now_parked_.at(car));
            complete_parks_[car] = dur;
            now_parked_.erase(car);
        }
        else 
        {
            throw ParkingException();
        }
    }

    // получить счёт за конкретный автомобиль
    int64_t GetCurrentBill(const VehiclePlate& car) const
    {
        if (now_parked_.count(car) == 0 && complete_parks_.count(car) == 0)
        {
            return 0;
        }
        int64_t num = 0;
        if (now_parked_.count(car) != 0)
        {         
             TimePoint end_time = Clock::now();
             Duration dur = (end_time - now_parked_.at(car));
             int64_t temp = 
                 chrono::duration_cast<chrono::seconds>(dur).count()
                 * cost_per_second_;
             num += temp;
        }
        if (complete_parks_.count(car) != 0)
        {
            int64_t temp  = 
                chrono::duration_cast<chrono::seconds>(complete_parks_.at(car)).count() 
                * cost_per_second_;
            num += temp;
        }
        
        return num;
    }

    // завершить расчётный период
    // те машины, которые находятся на парковке на данный момент, должны 
    // остаться на парковке, но отсчёт времени для них начинается с нуля
    unordered_map<VehiclePlate, int64_t, VehiclePlateHasher> EndPeriodAndGetBills() 
    {
        unordered_map<VehiclePlate, int64_t, VehiclePlateHasher> result;
        if (now_parked_.size() != 0)
        {
            for (auto it = now_parked_.begin(); it != now_parked_.end(); ++it)
            {
                const auto end_time = Clock::now();
                const auto time_ = it->second;
                const auto dur = (end_time - time_);
                int64_t cost = 
                    chrono::duration_cast<chrono::seconds>(dur).count() 
                    * cost_per_second_;
                result[it->first] = cost;
                it->second = Clock::now();
            }
        }
        if (complete_parks_.size() != 0)
        {
            for (auto it = complete_parks_.begin(); it != complete_parks_.end(); ++it)
            {
                if (result.find(it->first) == result.end())
                {
                    result[it->first] = 
                        chrono::duration_cast<chrono::seconds>(it->second).count()
                        * cost_per_second_;
                }
                else
                {
                    result[it->first] +=
                        chrono::duration_cast<chrono::seconds>(it->second).count()
                        * cost_per_second_;
                }
            }
        }
        complete_parks_.clear();
        return result;
    }

    // не меняйте этот метод
    auto& GetNowParked() const 
    {
        return now_parked_;
    }

    // не меняйте этот метод
    auto& GetCompleteParks() const 
    {
        return complete_parks_;
    }

private:
    int cost_per_second_;
    unordered_map<VehiclePlate, TimePoint, VehiclePlateHasher> now_parked_;
    unordered_map<VehiclePlate, Duration, VehiclePlateHasher> complete_parks_;
};

// эти часы удобно использовать для тестирования
// они покажут столько времени, сколько вы задали явно
class TestClock
{
public:
    using time_point = chrono::system_clock::time_point;
    using duration = chrono::system_clock::duration;

    static void SetNow(int seconds)
    {
        current_time_ = seconds;
    }

    static time_point now()
    {
        return start_point_ + chrono::seconds(current_time_);
    }

private:
    inline static time_point start_point_ = chrono::system_clock::now();
    inline static int current_time_ = 0;
};

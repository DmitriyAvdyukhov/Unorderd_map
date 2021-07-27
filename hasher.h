#pragma once
#include <string>

#include "vehicle_plate.h"

using namespace std;

class VehiclePlateHasher
{
public:
    size_t operator()(const VehiclePlate& plate) const
    {

        // измените эту функцию, чтобы она учитывала все данные номера
        // рекомендуется использовать метод ToString() и существующий 
        // класс hash<string>
        std::hash<string>hstr;
        return static_cast<size_t>(hstr(plate.ToString()));
    }
};

struct PlateHasherTrivial 
{
    size_t operator()(const VehiclePlate& plate) const 
    {
        return static_cast<size_t>(plate.GetDigits());
    }
};

struct PlateHasherRegion 
{
    size_t operator()(const VehiclePlate& plate) const     
    {
        return static_cast<size_t>(plate.GetDigits() + plate.GetRegion() * 1000);
    }
};

struct PlateHasherString 
{
    size_t operator()(const VehiclePlate& plate) const
    {
        return hasher(plate.ToString());
    }

    hash<string> hasher;
};

struct PlateHasherAll 
{
    size_t operator()(const VehiclePlate& plate) const
    {       
        size_t result = plate.GetDigits();
        result += 100;
        result += plate.GetRegion();
        size_t c1 = plate.GetLetters()[0] - 'A';
        size_t c2 = plate.GetLetters()[1] - 'A';
        size_t c3 = plate.GetLetters()[2] - 'A';
        size_t c = (c1 * 100 + c2) * 100 + c3;
        result *= 1000000;
        result += c;

        return result;;
    }
};
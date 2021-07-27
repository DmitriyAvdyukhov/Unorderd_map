#pragma once
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

class VehiclePlate
{
private:
    auto AsTuple() const
    {
        return tie(letters_, digits_, region_);
    }

public:
    bool operator==(const VehiclePlate& other) const
    {
        return AsTuple() == other.AsTuple();
    }

    VehiclePlate(char l0, char l1, int digits, char l2, int region)
        : letters_{ l0, l1, l2 }
        , digits_(digits)
        , region_(region)
    {}

    std::string ToString() const
    {
        std::ostringstream out;
        out << letters_[0] << letters_[1];

        // чтобы дополнить цифровую часть номера слева нулями
        // до трёх цифр, используем подобные манипуляторы:
        // setfill задаёт символ для заполнения,
        // right задаёт выравнивание по правому краю,
        // setw задаёт минимальное желаемое количество знаков
        out << setfill('0') << right << setw(3) << digits_;
        out << letters_[2] << setw(2) << region_;

        return out.str();
    }

    int Hash() const
    {
        return digits_;
    }

    const array<char, 3>& GetLetters() const
    {
        return letters_;
    }

    int GetDigits() const
    {
        return digits_;
    }

    int GetRegion() const
    {
        return region_;
    }

    
private:
    array<char, 3> letters_;
    int digits_;
    int region_;
};

ostream& operator<<(ostream& out, VehiclePlate plate) {
    out << plate.ToString();
    return out;
}



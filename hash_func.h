#pragma once
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "vehicle_plate.h"

using namespace std;

template <typename T>
class HashableContainer 
{
public:

    void Insert(T elem)
    {
        int index = elem.Hash();

        // если вектор недостаточно велик для этого индекса,
        // то увеличим его, выделив место с запасом
        if (index >= int(elements_.size())) 
        {
            elements_.resize(index * 2 + 1);
        }
        vector<T>& tmp = elements_[index];    

        if (find(tmp.begin(), tmp.end(), elem) == tmp.end())
        {
            tmp.push_back(move(elem));
        }
    }
    // если вектор недостаточно велик для этого индекса,
    // то увеличим его, выделив место с запасом


    void PrintAll(ostream& out) const
    {
        for (auto& e : elements_)
        {

            if (!e.size())
            {
                continue;
            }
            for (const auto& t : e)
                out << t << endl;
        }
    }

    const auto& GetVector() const
    {
        return elements_;
    }

private:
    vector<vector<T>> elements_{};
};

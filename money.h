#pragma once
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class MoneyBox {
public:
    explicit MoneyBox(vector<int64_t> nominals)
        : nominals_(move(nominals))
        , counts_(nominals_.size()) {
    }

    const vector<int>& GetCounts() const {
        return counts_;
    }


    void PushCoin(int64_t value) {

        for (int64_t pos = 0; pos < nominals_.size(); ++pos)
        {
            if (nominals_[pos] == value)
            {
                assert(pos < nominals_.size());
                ++counts_[pos];
            }
        }
    }

    void PrintCoins(ostream& out) const {
        for (int i = 0; i < counts_.size(); ++i)
        {
            if (counts_[i] != 0)
            {
                out << nominals_[i] << ": "s << counts_[i] << endl;
            }
        }
    }



private:
    const vector<int64_t> nominals_;
    vector<int> counts_;
};

ostream& operator<<(ostream& out, const MoneyBox& cash) {
    cash.PrintCoins(out);
    return out;
}
#include "money.h"
#include "hash_func.h"
#include "unordered_map.h"
#include "unoreder_set.h"

using namespace std;

int main() {
    //money
   /* {
        cout << "money\n"s << endl;
        MoneyBox cash({ 10, 50, 100, 200, 500, 1000, 2000, 5000 });

        int times;
        cout << "Enter number of coins you have:"s << endl;
        cin >> times;

        cout << "Enter all nominals:"s << endl;
        for (int i = 0; i < times; ++i) {
            int64_t value;
            cin >> value;
            cash.PushCoin(value);
        }
        cout << cash << endl;
    }*/
    cout << endl;
     //hash_func
    {
        cout << "hash_func\n"s << endl;
        HashableContainer<VehiclePlate> plate_base;
        plate_base.Insert({ 'B', 'H', 840, 'E', 99 });
        plate_base.Insert({ 'O', 'K', 942, 'K', 78 });
        plate_base.Insert({ 'O', 'K', 942, 'K', 78 });
        plate_base.Insert({ 'O', 'K', 942, 'K', 78 });
        plate_base.Insert({ 'O', 'K', 942, 'K', 78 });
        plate_base.Insert({ 'H', 'E', 968, 'C', 79 });
        plate_base.Insert({ 'T', 'A', 326, 'X', 83 });
        plate_base.Insert({ 'H', 'H', 831, 'P', 116 });
        plate_base.Insert({ 'P', 'M', 884, 'K', 23 });
        plate_base.Insert({ 'O', 'C', 34, 'P', 24 });
        plate_base.Insert({ 'M', 'Y', 831, 'M', 43 });
        plate_base.Insert({ 'K', 'T', 478, 'P', 49 });
        plate_base.Insert({ 'X', 'P', 850, 'A', 50 });

        plate_base.PrintAll(cout);
    }
    cout << endl;

    //unordered_map
    {
        cout << "unordered_map\n"s << endl;
        ParkingCounter parking;

        parking.Park({ 'B', 'H', 840, 'E', 99 });
        parking.Park({ 'O', 'K', 942, 'K', 78 });
        parking.Park({ 'O', 'K', 942, 'K', 78 });
        parking.Park({ 'O', 'K', 942, 'K', 78 });
        parking.Park({ 'O', 'K', 942, 'K', 78 });
        parking.Park({ 'H', 'E', 968, 'C', 79 });
        parking.Park({ 'T', 'A', 326, 'X', 83 });
        parking.Park({ 'H', 'H', 831, 'P', 116 });
        parking.Park({ 'A', 'P', 831, 'Y', 99 });
        parking.Park({ 'P', 'M', 884, 'K', 23 });
        parking.Park({ 'O', 'C', 34, 'P', 24 });
        parking.Park({ 'M', 'Y', 831, 'M', 43 });
        parking.Park({ 'B', 'P', 831, 'M', 79 });
        parking.Park({ 'O', 'K', 942, 'K', 78 });
        parking.Park({ 'K', 'T', 478, 'P', 49 });
        parking.Park({ 'X', 'P', 850, 'A', 50 });

        assert(parking.GetCount({ 'O', 'K', 942, 'K', 78 }) == 5);
        assert(parking.GetCount({ 'A', 'B', 111, 'C', 99 }) == 0);

        for (const auto& [plate, count] : parking.GetAllData()) {
            cout << plate << " "s << count << endl;
        }
    }
    cout << endl;

    cout << "unordered_set\n"s << endl;
    {
        Parking<TestClock> parking(10);

        TestClock::SetNow(10);
        parking.Park({ 'A', 'A', 111, 'A', 99 });

        TestClock::SetNow(20);
        parking.Withdraw({ 'A', 'A', 111, 'A', 99 });
        parking.Park({ 'B', 'B', 222, 'B', 99 });

        TestClock::SetNow(40);
        assert(parking.GetCurrentBill({ 'A', 'A', 111, 'A', 99 }) == 100);
        assert(parking.GetCurrentBill({ 'B', 'B', 222, 'B', 99 }) == 200);
        parking.Park({ 'A', 'A', 111, 'A', 99 });

        TestClock::SetNow(50);
        assert(parking.GetCurrentBill({ 'A', 'A', 111, 'A', 99 }) == 200);
        assert(parking.GetCurrentBill({ 'B', 'B', 222, 'B', 99 }) == 300);
        assert(parking.GetCurrentBill({ 'C', 'C', 333, 'C', 99 }) == 0);
        parking.Withdraw({ 'B', 'B', 222, 'B', 99 });

        TestClock::SetNow(70);
        {
            // проверим счёт
            auto bill = parking.EndPeriodAndGetBills();

            // так как внутри макроса используется запятая,
            // нужно заключить его аргумент в дополнительные скобки
            assert((bill
                == unordered_map<VehiclePlate, int64_t, VehiclePlateHasher>{
                    { {'A', 'A', 111, 'A', 99}, 400},
                    { {'B', 'B', 222, 'B', 99}, 300 },
            }));
        }

        TestClock::SetNow(80);
        {
            // проверим счёт
            auto bill = parking.EndPeriodAndGetBills();

            // так как внутри макроса используется запятая,
            // нужно заключить его аргумент в дополнительные скобки
            assert((bill
                == unordered_map<VehiclePlate, int64_t, VehiclePlateHasher>{
                    { {'A', 'A', 111, 'A', 99}, 100},
            }));
        }

        try {
            parking.Park({ 'A', 'A', 111, 'A', 99 });
            assert(false);
        }
        catch (ParkingException) {
        }

        try {
            parking.Withdraw({ 'B', 'B', 222, 'B', 99 });
            assert(false);
        }
        catch (ParkingException) {
        }

        cout << "Success!"s << endl;
    }

    return 0;
}
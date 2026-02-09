#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
public:
    Truck() : Vehicle() {}
    Truck(const char* vNum, int rent) : Vehicle(vNum, rent) {}
    ~Truck() {}

    int calculateRent(int days) override {
        // Truck has 15% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 15 / 100;
        return baseRent + serviceCharge;
    }

    void displayInfo() const override {
        cout << "\n--- TRUCK ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 15% extra" << endl;
    }

    const char* getType() const override {
        return "Truck";
    }

    float fuelAverage() const override {
        return 6.0;    // 6 km per liter
    }
};

#endif // TRUCK_H

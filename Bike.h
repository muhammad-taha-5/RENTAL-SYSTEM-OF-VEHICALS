#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"

class Bike : public Vehicle {
public:
    Bike() : Vehicle() {}
    Bike(const char* vNum, int rent) : Vehicle(vNum, rent) {}
    ~Bike() {}

    int calculateRent(int days) override {
        // Bike has 5% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 5 / 100;
        return baseRent + serviceCharge;
    }

    void displayInfo() const override {
        cout << "\n--- BIKE ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 5% extra" << endl;
    }

    const char* getType() const override {
        return "Bike";
    }

    float fuelAverage() const override {
        return 40.0;   // 40 km per liter
    }
};

#endif // BIKE_H

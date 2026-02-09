#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
public:
    Car() : Vehicle() {}
    Car(const char* vNum, int rent) : Vehicle(vNum, rent) {}
    ~Car() {}

    int calculateRent(int days) override {
        // Car has 10% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 10 / 100;
        return baseRent + serviceCharge;
    }

    void displayInfo() const override {
        cout << "\n--- CAR ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 10% extra" << endl;
    }

    const char* getType() const override {
        return "Car";
    }

    float fuelAverage() const override {
        return 12.0;   // 12 km per liter
    }
};

#endif // CAR_H

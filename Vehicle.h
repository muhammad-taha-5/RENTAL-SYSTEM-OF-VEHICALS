#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <cstring>
#include "Utils.h" // For color::Green

using namespace std;

// ============================================
// ABSTRACT BASE CLASS - Vehicle (Abstraction)
// ============================================
class Vehicle {
private:
    char vehicleNumber[20];
    int rentPerDay;
    bool isAvailable;
    bool underMaintenance;

protected:
    // Encapsulation: Protected setters for derived classes
    void setVehicleNumber(const char* vNum);
    void setRentPerDay(int rent);

public:
    Vehicle();
    Vehicle(const char* vNum, int rent);
    virtual ~Vehicle(); // Virtual Destructor

    void setMaintenance(bool status);
    bool isUnderMaintenance() const;

    const char* getVehicleNumber() const;
    int getRentPerDay() const;
    bool getAvailability() const;
    void setAvailability(bool status);

    // Pure Virtual Function (Abstraction)
    virtual int calculateRent(int days) = 0;

    // Virtual function for displaying vehicle info
    virtual void displayInfo() const;

    void setRent(int rent);

    virtual float fuelAverage() const = 0;   // km per liter
    virtual const char* getType() const = 0;
};

#endif // VEHICLE_H

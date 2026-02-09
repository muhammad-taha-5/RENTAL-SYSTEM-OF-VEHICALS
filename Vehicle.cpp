#include "Vehicle.h"

Vehicle::Vehicle() {
    strcpy(vehicleNumber, "N/A");
    rentPerDay = 0;
    isAvailable = true;
    underMaintenance = false;
}

Vehicle::Vehicle(const char* vNum, int rent) {
    strcpy(vehicleNumber, vNum);
    
    // Use Setter for Validation (prevent invalid rent)
    setRentPerDay(rent);
    
    isAvailable = true;
    underMaintenance = false;
}

Vehicle::~Vehicle() {
    // Cleanup if needed
}

void Vehicle::setVehicleNumber(const char* vNum) {
    strcpy(vehicleNumber, vNum);
}

void Vehicle::setRentPerDay(int rent) {
    if (rent < 0) {
        cout << "Error: Rent cannot be negative!" << endl;
        rentPerDay = 1000; // Default fallback
    } else {
        rentPerDay = rent;
    }
}

void Vehicle::setMaintenance(bool status) {
    underMaintenance = status;
}

bool Vehicle::isUnderMaintenance() const {
    return underMaintenance;
}

const char* Vehicle::getVehicleNumber() const {
    return vehicleNumber;
}

int Vehicle::getRentPerDay() const {
    return rentPerDay;
}

bool Vehicle::getAvailability() const {
    return isAvailable;
}

void Vehicle::setAvailability(bool status) {
    isAvailable = status;
}

void Vehicle::displayInfo() const {
    cout << color::Green << "Vehicle Number: " << vehicleNumber << endl;
    cout << "Rent Per Day: Rs. " << rentPerDay << endl;

    if (underMaintenance) {
        cout << "Status: UNDER MAINTENANCE" << endl;
    }
    else {
        cout << "Status: " << (isAvailable ? "Available" : "Rented") << endl;
    }
}

void Vehicle::setRent(int rent) {
    // Input Validation
    if (rent < 500) {
        cout << "Warning: Minimum rent is 500. Setting to 500." << endl;
        rentPerDay = 500;
    } else if (rent > 20000) {
        cout << "Warning: Maximum rent is 20000. Setting to 20000." << endl;
        rentPerDay = 20000;
    } else {
        rentPerDay = rent;
    }
}

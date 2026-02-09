#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include "Truck.h"
#include "Customer.h"
#include "Admin.h"
#include "Utils.h"
#include "Invoice.h"
#include <fstream>

class RentalSystem {
private:
    Vehicle* vehicles[20];
    int totalVehicles;
    Customer customer;
    Admin admin;
    int rentPerDay;

    bool vehicleExists(const char* vNum);

public:
    RentalSystem();
    ~RentalSystem();

    void initializeVehicles();
    void registerCustomer();
    void showAvailableVehicles();
    void rentVehicleMenu();
    void returnVehicleMenu();
    void saveToFile();
    void viewRentalHistory();
    void searchVehicle();
    void calculateEstimatedCost();
    void addNewVehicle();
    void modifyRentRate();
    void vehicleMaintenanceMenu();
    void adminMenu();
    void displayMenu();
};

#endif // RENTALSYSTEM_H

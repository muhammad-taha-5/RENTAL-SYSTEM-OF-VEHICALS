#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Vehicle.h"
#include "Utils.h"
#include "Invoice.h"

// ============================================
// CUSTOMER CLASS - Manages Rentals
// ============================================
class Customer : public User {
private:
    char rentedVehicleNumber[20];
    bool hasRentedVehicle;
    bool isVIP; // Polymorphic Discount Flag
    Date expiryDate; // Membership Expiry
       
    //  atributes of the receipt  
    int rentedDays;
    int actualDays;
    int lateDays;
    int distanceKM;
    float fuelUsed;
    int totalBill;

public:
    Customer();
    Customer(const char* name, bool vipStatus);
    virtual ~Customer();

    const char* getRole() const override;

    bool hasRented() const;
    const char* getRentedVehicle() const;
    bool isMembershipExpired();

    void rentVehicle(Vehicle* vehicle, int days);
    void returnVehicle(Vehicle* vehicles[], int totalVehicles);
    void generateReceipt(Vehicle* vehicle);
};

#endif // CUSTOMER_H

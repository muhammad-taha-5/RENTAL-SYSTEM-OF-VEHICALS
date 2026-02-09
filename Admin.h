#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Vehicle.h"
#include "Utils.h"

class Admin : public User {
private:
    char password[20];
    bool loggedIn;

public:
    Admin();
    
    bool login();
    void logout();
    bool isLoggedIn() const;
    const char* getRole() const override;

    // Role-Specific Functionality
    void deleteRecord(Vehicle* vehicles[], int& totalVehicles);
    void resetPassword();
};

#endif // ADMIN_H

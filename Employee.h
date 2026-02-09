#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:
    Employee() : User() {}
    Employee(const char* n) : User(n) {} // Auto ID for Employee too

    const char* getRole() const override {
        return "Employee";
    }
};

#endif // EMPLOYEE_H

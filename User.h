#ifndef USER_H
#define USER_H

#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

// ============================================
// ABSTRACT BASE CLASS - User (Role-Based Access)
// ============================================
class User {
protected:
    char name[50];
    char id[20];
    static int userCount; // Static variable for ID generation

public:
    User();
    User(const char* n);
    User(const char* n, const char* i); // Constructor for explicit ID

    virtual ~User();

    const char* getName() const;
    const char* getID() const;

    virtual const char* getRole() const = 0;
};

#endif // USER_H

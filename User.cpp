#include "User.h"

// Initialize static member
int User::userCount = 0;

User::User() {
    strcpy(name, "");
    strcpy(id, "");
}

User::User(const char* n) {
    strcpy(name, n);
    userCount++;
    sprintf(id, "USR-%d", 1000 + userCount); // Auto-generate ID (e.g., USR-1001)
}

// Constructor for explicit ID (used by Admin)
User::User(const char* n, const char* i) {
    strcpy(name, n);
    strcpy(id, i);
}

User::~User() {}

const char* User::getName() const {
    return name;
}

const char* User::getID() const {
    return id;
}

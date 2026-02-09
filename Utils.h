#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits> // for std::numeric_limits

using namespace std;

namespace color {
    const string Green = "\033[32m";
}

// ============================================
// DATE CLASS - Membership Expiry
// ============================================
class Date {
private:
    int day, month, year;

public:
    // Default Constructor
    Date() : day(1), month(1), year(2026) {}

    // Parameterized Constructor
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Method to check if this date is expired compared to "today"
    // Returns true if THIS date is BEFORE the current date
    bool isExpired(int currD, int currM, int currY) const {
        if (year < currY) return true;
        if (year == currY && month < currM) return true;
        if (year == currY && month == currM && day < currD) return true;
        return false;
    }

    // Helper to display the date
    void displayDate() const {
        cout << (day < 10 ? "0" : "") << day << "/"
             << (month < 10 ? "0" : "") << month << "/" << year;
    }
};

// Function Prototype
int getSafeIntInput(int min, int max);

#endif // UTILS_H

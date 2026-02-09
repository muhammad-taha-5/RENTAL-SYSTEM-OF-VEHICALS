#include "Admin.h"

Admin::Admin() : User("admin", "ADM-001") {
    strcpy(password, "1234");
    loggedIn = false;
}

bool Admin::login() {
    char u[20], p[20];

    cout << "\n========== ADMIN LOGIN ==========" << endl;
    cout << "Enter Admin ID: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;

    if (strcmp(u, id) == 0 && strcmp(p, password) == 0) {
        loggedIn = true;
        cout << "\n Admin login successful!" << endl;
        return true;
    }

    cout << "\n Invalid admin credentials!" << endl;
    return false;
}

void Admin::logout() {
    loggedIn = false;
    cout << "\nAdmin logged out successfully." << endl;
}

bool Admin::isLoggedIn() const {
    return loggedIn;
}

const char* Admin::getRole() const {
    return "Admin";
}

void Admin::deleteRecord(Vehicle* vehicles[], int& totalVehicles) {
    if (!loggedIn) {
        cout << "\n[Error] Access Denied! Login required." << endl;
        return;
    }

    char vNum[20];
    bool found = false;
    cout << "\n========== DELETE RECORD (ADMIN) ==========" << endl;
    cout << "Enter Vehicle Number to Delete: ";
    cin >> vNum;

    for (int i = 0; i < totalVehicles; i++) {
        if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {
            
            // Delete the object from memory
            delete vehicles[i];

            // Shift remaining vehicles left
            for (int j = i; j < totalVehicles - 1; j++) {
                vehicles[j] = vehicles[j + 1];
            }

            totalVehicles--; // Decrease count
            found = true;
            cout << "\n[Admin] Vehicle " << vNum << " deleted successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "\n[Admin] Vehicle not found!" << endl;
    }
}

void Admin::resetPassword() {
    if (!loggedIn) {
        cout << "\n[Error] Access Denied! Login required." << endl;
        return;
    }

    char oldPass[20];
    cout << "\n========== RESET PASSWORD ==========" << endl;
    cout << "Enter Old Password: ";
    cin >> oldPass;

    if (strcmp(oldPass, password) == 0) {
        cout << "Enter New Password: ";
        cin >> password;
        cout << "\n[Success] Password changed successfully!" << endl;
    } else {
        cout << "\n[Error] Incorrect old password!" << endl;
    }
}

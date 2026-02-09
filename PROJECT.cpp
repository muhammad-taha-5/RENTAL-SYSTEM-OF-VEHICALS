#define _CRT_SECURE_NO_WARNINGS  // it is for the string function and remove the warnings  
#include <iostream>
#include <fstream>
#include <cstring>
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

// ============================================
// INVOICE CLASS - Billing Encapsulation & Operator Overloading
// ============================================
class Invoice {
private:
    double totalAmount;
    char details[200]; // Description of charges

public:
    Invoice() : totalAmount(0.0) {
        strcpy(details, "Empty Invoice");
    }

    Invoice(double amount, const char* desc) : totalAmount(amount) {
        strncpy(details, desc, 199);
        details[199] = '\0';
    }

    // Operator Overloading (+) to combine two invoices
    // Example: Car Rent Invoice + Driver Service Invoice
    Invoice operator+(const Invoice& other) {
        double newTotal = this->totalAmount + other.totalAmount;
        
        char newDetails[200];
        // Combine descriptions: "Car Rent" + "Driver" -> "Car Rent, Driver"
        if (strlen(this->details) + strlen(other.details) + 2 < 200) {
             sprintf(newDetails, "%s + %s", this->details, other.details);
        } else {
             strcpy(newDetails, "Combined Invoice");
        }

        return Invoice(newTotal, newDetails);
    }

    void display() const {
        cout << "-----------------------------" << endl;
        cout << "Invoice Details : " << details << endl;
        cout << "Total Amount    : Rs. " << totalAmount << endl;
        cout << "-----------------------------" << endl;
    }

    double getAmount() const {
        return totalAmount;
    }
};

// ============================================
// ABSTRACT BASE CLASS - User (Role-Based Access)
// ============================================
class User {
protected:
    char name[50];
    char id[20];
    static int userCount; // Static variable for ID generation

public:
    User() {
        strcpy(name, "");
        strcpy(id, "");
    }

    User(const char* n) {
        strcpy(name, n);
        userCount++;
        sprintf(id, "USR-%d", 1000 + userCount); // Auto-generate ID (e.g., USR-1001)
    }

    // Constructor for explicit ID (used by Admin)
    User(const char* n, const char* i) {
        strcpy(name, n);
        strcpy(id, i);
    }

    virtual ~User() {}

    const char* getName() const {
        return name;
    }

    const char* getID() const {
        return id;
    }

    virtual const char* getRole() const = 0;
};

// Initialize static member
int User::userCount = 0;

class Employee : public User {
public:
    Employee() : User() {}
    Employee(const char* n) : User(n) {} // Auto ID for Employee too

    const char* getRole() const override {
        return "Employee";
    }
};

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

    void setVehicleNumber(const char* vNum) {
        strcpy(vehicleNumber, vNum);
    }

    void setRentPerDay(int rent) {
        if (rent < 0) {
            cout << "Error: Rent cannot be negative!" << endl;
            rentPerDay = 1000; // Default fallback
        } else {
            rentPerDay = rent;
        }
    }


public:
    
    Vehicle() {
        strcpy(vehicleNumber, "N/A");
        rentPerDay = 0;
        isAvailable = true;
        underMaintenance = false;
    }

    Vehicle(const char* vNum, int rent) {
        strcpy(vehicleNumber, vNum);
        
        // Use Setter for Validation (prevent invalid rent)
        setRentPerDay(rent);
        
        isAvailable = true;
        underMaintenance = false;
    }
  
    // Destructor (Virtual for Resource Management)
    virtual ~Vehicle() {
        // Cleanup if needed (e.g. if we had dynamic members)
        // cout << "Vehicle " << vehicleNumber << " destroyed." << endl;
    }



    // ✅ MAKE THESE PUBLIC
    void setMaintenance(bool status) {
        underMaintenance = status;
    }

    bool isUnderMaintenance() const {
        return underMaintenance;
    }

    // Encapsulation: Getters
    const char* getVehicleNumber() const {
        return vehicleNumber;
    }

    int getRentPerDay() const {
        return rentPerDay;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    // Pure Virtual Function (Abstraction)
    virtual int calculateRent(int days) = 0;

    // Virtual function for displaying vehicle info
    virtual void displayInfo() const {
        cout << color::Green << "Vehicle Number: " << vehicleNumber << endl;

        cout << "Rent Per Day: Rs. " << rentPerDay << endl;

        if (underMaintenance) {
            cout << "Status: UNDER MAINTENANCE" << endl;
        }
        else {
            cout << "Status: " << (isAvailable ? "Available" : "Rented") << endl;
        }
    }



    void setRent(int rent) {
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

    virtual float fuelAverage() const = 0;   // km per liter

    // Virtual function to get vehicle type
    virtual const char* getType() const = 0;
};

// ============================================
// DERIVED CLASS - Car (Inheritance)
// ============================================
class Car : public Vehicle {
public:
    // Constructor
    Car() : Vehicle() {}

    Car(const char* vNum, int rent) : Vehicle(vNum, rent) {}

    // Destructor
    ~Car() {}

    // Polymorphism: Override calculateRent
    int calculateRent(int days) {
        // Car has 10% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 10 / 100;
        return baseRent + serviceCharge;
    }

    // Override displayInfo
    void displayInfo() const {
        cout << "\n--- CAR ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 10% extra" << endl;
    }


    const char* getType() const {
        return "Car";
    }





    float fuelAverage() const {
        return 12.0;   // 12 km per liter
    }
};

// ============================================
// DERIVED CLASS - Bike (Inheritance)
// ============================================
class Bike : public Vehicle {
public:
    // Constructor
    Bike() : Vehicle() {}

    Bike(const char* vNum, int rent) : Vehicle(vNum, rent) {}

    // Destructor
    ~Bike() {}

    // Polymorphism: Override calculateRent
    int calculateRent(int days) {
        // Bike has 5% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 5 / 100;
        return baseRent + serviceCharge;
    }

    // Override displayInfo
    void displayInfo() const {
        cout << "\n--- BIKE ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 5% extra" << endl;
    }

    const char* getType() const {
        return "Bike";
    }




    float fuelAverage() const {
        return 40.0;   // 40 km per liter
    }
};


// ============================================
// DERIVED CLASS - Truck (Inheritance)
// ============================================
class Truck : public Vehicle {
public:
    // Constructor
    Truck() : Vehicle() {}

    Truck(const char* vNum, int rent) : Vehicle(vNum, rent) {}

    // Destructor
    ~Truck() {}

    // Polymorphism: Override calculateRent
    int calculateRent(int days) {
        // Truck has 15% service charge
        int baseRent = getRentPerDay() * days;
        int serviceCharge = baseRent * 15 / 100;
        return baseRent + serviceCharge;
    }

    // Override displayInfo
    void displayInfo() const {
        cout << "\n--- TRUCK ---" << endl;
        Vehicle::displayInfo();
        cout << "Service Charge: 15% extra" << endl;
    }

    const char* getType() const {
        return "Truck";
    }




    float fuelAverage() const {
        return 6.0;    // 6 km per liter
    }
};


int getSafeIntInput(int min, int max) {
    int value;
    while (true) {
        cin >> value;

        if (cin.fail()) {
            cin.clear();                      // clear error
            cin.ignore(1000, '\n');           // discard wrong input
            cout << "Invalid input! Enter a number: ";
        }
        else if (value < min || value > max) {
            cout << "Please enter a number between "
                << min << " and " << max << ": ";
        }
        else {
            cin.ignore(1000, '\n');  // clean buffer
            return value;
        }
    }
}

bool customerExistsInFile(const char* name, const char* id) {
    ifstream file("rentals.txt");
    if (!file.is_open()) {
        return false;   // File doesn't exist yet
    }

    char line[300];

    while (file.getline(line, 300)) {
        // Check BOTH name and ID in the same line
        if (strstr(line, name) && strstr(line, id)) {
            file.close();
            return true;   // Duplicate found
        }
    }

    file.close();
    return false;   // No duplicate
}

// ============================================
// CUSTOMER CLASS - Manages Rentals
// ============================================
//Difference between struct and class
//In C++, they are almost identical!The only real difference is :
//struct : Members are public by default (anyone can see / change them).
// //  class : Members are private by default (they are hidden for safety).// even  we have used  the (private ) class here!  


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
    // Constructor
    Customer() : User() {
        strcpy(rentedVehicleNumber, "");
        hasRentedVehicle = false;
        isVIP = false;
        
        // //  atributes of the receipt
        rentedDays = 0;
        actualDays = 0;
        lateDays = 0;
        distanceKM = 0;
        fuelUsed = 0;
        totalBill = 0;

    }

    Customer(const char* name, bool vipStatus) : User(name) {
        strcpy(rentedVehicleNumber, "");
        hasRentedVehicle = false;
        isVIP = vipStatus;
        if (isVIP) {
            // VIP gets 1 year validity
            expiryDate = Date(8, 2, 2030); 
        } else {
            // Regular gets 6 months (just an example)
            expiryDate = Date(8, 8, 2026);
        }
    }

    // Destructor
    ~Customer() {}

    // Role
    const char* getRole() const override {
        return "Customer";
    }

    bool hasRented() const {
        return hasRentedVehicle;
    }

    const char* getRentedVehicle() const {
        return rentedVehicleNumber;
    }

    // Check if membership is expired (Simulated Today: 8/2/2026)
    bool isMembershipExpired() {
        // Hardcoded "Today's Date" for simulation
        // In real app, we'd use system time
        return expiryDate.isExpired(8, 2, 2026);
    }

    // Rent a vehicle

    void rentVehicle(Vehicle* vehicle, int days) {

        if (isMembershipExpired()) {
            cout << "\n[!] Membership EXPIRED on ";
            expiryDate.displayDate();
            cout << ". Please renew to rent vehicles." << endl;
            return;
        }

        if (hasRentedVehicle) {
            cout << "\nYou already have a rented vehicle!" << endl;
            return;
        }

        if (vehicle->isUnderMaintenance()){
            cout << "\nThis vehicle is under maintenance and cannot be rented!" << endl;
            return;
        }

        if (!vehicle->getAvailability()) {
            cout << "\nThis vehicle is not available!" << endl;
            return;
        }

        int totalRent = vehicle->calculateRent(days);
    
    // Store original rent for calculation
    int finalRent = totalRent;
    int discount = 0;

    cout << "\n========== RENTAL CONFIRMATION ==========" << endl;
    cout << "Customer: " << name << endl;
    cout << "Vehicle Number: " << vehicle->getVehicleNumber() << endl;
    cout << "Vehicle Type: " << vehicle->getType() << endl;
    cout << "Rent Per Day: Rs. " << vehicle->getRentPerDay() << endl;
    cout << "Number of Days: " << days << endl;
    cout << "Base Rent (inc. charges): Rs. " << totalRent << endl;
    
    if (isVIP) {
        discount = totalRent * 15 / 100;
        finalRent = totalRent - discount;
        cout << color::Green << "VIP Discount (15%): -Rs. " << discount << "\033[0m" << endl;

    }

    cout << "Total Payable Rent: Rs. " << finalRent << endl;
    cout << "=========================================" << endl;

    vehicle->setAvailability(false);
    strcpy(rentedVehicleNumber, vehicle->getVehicleNumber());
    hasRentedVehicle = true;

    rentedDays = days;
    totalBill = totalRent; // Store BASE rent for later receipt calculation (receipt applies discount too)
    // NOTE: In current logic, generateReceipt RE-APPLIES discount to (totalBill + Fines). 
    // This is consistent for now.

    cout << "\nVehicle rented successfully!" << endl;
    }

    void returnVehicle(Vehicle* vehicles[], int totalVehicles) {
        if (!hasRentedVehicle) {
            cout << "\nYou don't have any rented vehicle!" << endl;
            return;
        }

        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), rentedVehicleNumber) == 0) {

                generateReceipt(vehicles[i]);

                vehicles[i]->setAvailability(true);
                strcpy(rentedVehicleNumber, "");
                hasRentedVehicle = false;

                cout << "\nVehicle returned successfully!" << endl;
                return;
            }
        }
    }




    void generateReceipt(Vehicle* vehicle) {
        const int lateFinePerDay = 500;   // Rs. 500 per late day

        cout << "\nEnter actual days used: ";
        actualDays = getSafeIntInput(0, 365);

        cout << "Enter number of late days: ";
        lateDays = getSafeIntInput(0, 100);   // user explicitly enters late days

        cout << "Enter distance travelled (KM): ";
        distanceKM = getSafeIntInput(0, 5000);


        // Calculate late fine
        int lateFine =  +lateDays * vehicle->getRentPerDay()+  lateFinePerDay ;

        // Fuel consumption
        fuelUsed = distanceKM / vehicle->fuelAverage();

        // Add late fine to bill
        totalBill += lateFine;

        // --- POLYMORPHIC DISCOUNT LOGIC ---
        float discount = 0.0;
        if (isVIP) {
            discount = totalBill * 0.15; // 15% Discount for VIP
        }
        totalBill -= (int)discount;

        totalBill -= (int)discount;

        // ================= INVOICE =================
        Invoice finalInvoice(totalBill, "Vehicle Rental"); // Using Invoice Class
        
        cout << "\n============= RENTAL INVOICE =============" << endl;
        cout << "Customer Name   : " << name << endl;
        if (isVIP) cout << "Membership      : " << color::Green << "VIP (15% OFF)" << "\033[0m" << endl;

        else       cout << "Membership      : Regular" << endl;
        cout << "Valid Until     : "; expiryDate.displayDate(); cout << endl;
        cout << "Customer ID     : " << id  << endl;
        cout << "Vehicle Number  : " << vehicle->getVehicleNumber() << endl;
        cout << "Vehicle Type    : " << vehicle->getType() << endl;
        cout << "Rent Per Day    : Rs. " << vehicle->getRentPerDay() << endl;
        cout << "Days Rented     : " << rentedDays << endl;
        cout << "Actual Days     : " << actualDays << endl;
        cout << "Late Days       : " << lateDays << endl;
        cout << "Late Fine       : Rs. " << lateFine << endl;
        cout << "Distance (KM)   : " << distanceKM << endl;
        cout << "Fuel Average    : " << vehicle->fuelAverage() << " km/l" << endl;
        cout << "Fuel Consumed   : " << fuelUsed << " liters" << endl;
        cout << "------------------------------------------" << endl;
        if (isVIP) {
            cout << "Subtotal        : Rs. " << (totalBill + (int)discount) << endl;
            cout << "Discount        : -Rs. " << (int)discount << endl;
        }
        cout << "TOTAL BILL      : Rs. " << finalInvoice.getAmount() << endl;
        cout << "==========================================" << endl;
    }

    


};



class Admin : public User {

private:
   // char username[20]; // Using 'name' from User as username
    char password[20];
    bool loggedIn;

public:
    Admin() : User("admin", "ADM-001") {
        strcpy(password, "1234");
        loggedIn = false;
    }

    bool login() {
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

    void logout() {
        loggedIn = false;
        cout << "\nAdmin logged out successfully." << endl;
    }

    bool isLoggedIn() const {
        return loggedIn;
    }

    const char* getRole() const override {
        return "Admin";
    }

    // Role-Specific Functionality: Delete a Vehicle
    void deleteRecord(Vehicle* vehicles[], int& totalVehicles) {
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

    void resetPassword() {
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

};







// ============================================
// RENTAL SYSTEM CLASS - Main Management
// ============================================
class RentalSystem {
private:
    Vehicle* vehicles[20];
    int totalVehicles;
    Customer customer;   //  this the object of the upper class customer  ?? 
    int  rentPerDay;

    bool vehicleExists(const char* vNum) {
        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {
                return true;
            }
        }
        return false;
    }


public:
    // Constructor
    RentalSystem() {
        totalVehicles = 0;
        initializeVehicles();
    }

    // Destructor
    ~RentalSystem() {
        for (int i = 0; i < totalVehicles; i++) {
            delete vehicles[i];
        }
    }

    // Initialize sample vehicles
    void initializeVehicles() {
        vehicles[totalVehicles++] = new Car("CAR-001", 3000);
        vehicles[totalVehicles++] = new Car("CAR-002", 3500);
        vehicles[totalVehicles++] = new Car("CAR-003", 4000);

        vehicles[totalVehicles++] = new Bike("BIKE-001", 800);
        vehicles[totalVehicles++] = new Bike("BIKE-002", 1000);
        vehicles[totalVehicles++] = new Bike("BIKE-003", 1200);

        vehicles[totalVehicles++] = new Truck("TRUCK-001", 5000);
        vehicles[totalVehicles++] = new Truck("TRUCK-002", 5500);
        vehicles[totalVehicles++] = new Truck("TRUCK-003", 6000);
    }

    void registerCustomer() {
        char name[50];
        int typeChoice;
        bool vip = false;

        cout << "\n========== CUSTOMER REGISTRATION ==========" << endl;

        while (true) {
            cout << "Enter your name: ";
           // cin.ignore(100, '\n');   // flush entire buffer
            cin.getline(name, 50);

            // Removed manual ID entry
            // ID Checks removed because IDs are now unique by design

             {
                cout << "Select Membership Type:" << endl;
                cout << "1. Regular" << endl;
                cout << "2. VIP (Get 15% Discount)" << endl;
                cout << "Enter choice: ";
                typeChoice = getSafeIntInput(1, 2);
                
                if (typeChoice == 2) vip = true;

                customer = Customer(name, vip);
                cout << "\nCustomer registered successfully!" << endl;
                cout << "Your Assigned ID is: " << customer.getID() << endl;
                break;   //  exit loop safely
            }
        }
    }


    // Display available vehicles
    void showAvailableVehicles() {
        cout << "\n========== AVAILABLE VEHICLES ==========" << endl;
        bool found = false;

        for (int i = 0; i < totalVehicles; i++) {
            if (vehicles[i]->getAvailability()) {
                vehicles[i]->displayInfo();
                found = true;
            }
        }

        if (!found) {
            cout << "No vehicles available at the moment." << endl;
        }
    }

    // Rent vehicle menu
    void rentVehicleMenu() {
        if (strlen(customer.getName()) == 0) {
            cout << "\nPlease register first!" << endl;
            return;
        }

        char vNumber[20];
        int days;

        showAvailableVehicles();

        cout << "\nEnter vehicle number to rent: ";
        cin >> vNumber;
        cout << "Enter number of days: ";
        cin >> days;

        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), vNumber) == 0) {
                customer.rentVehicle(vehicles[i], days);
                saveToFile();
                return;
            }
        }

        cout << "\nVehicle not found!" << endl;
    }

    // Return vehicle menu
    void returnVehicleMenu() {
        if (strlen(customer.getName()) == 0) {
            cout << "\nPlease register first!" << endl;
            return;
        }

        customer.returnVehicle(vehicles, totalVehicles);
        saveToFile();
    }

    // Save rental data to file
    void saveToFile() {
        ofstream file("rentals.txt", ios::app);
        if (file.is_open()) {
            file << "Customer: " << customer.getName()
                << " | ID: " << customer.getID();
            if (customer.hasRented()) {
                file << " | Rented: " << customer.getRentedVehicle();
            }
            else {
                file << " |  this  person  was  just vistor in  our ' RentalSystem ' <<" << endl;
            }

            file << endl;
            file.close();
        }
    }

    // View Rental History from file
    void viewRentalHistory() {
        ifstream file("rentals.txt");

        if (!file.is_open()) {
            cout << "\nNo rental history found!" << endl;
            return;
        }

        cout << "\n========== RENTAL HISTORY ==========" << endl;
        char line[200];
        int count = 1;

        while (file.getline(line, 200)) {
            cout << count << ". " << line << endl;
            count++;
        }

        if (count == 1) {
            cout << "No records found." << endl;
        }

        file.close();
        cout << "====================================" << endl;
    }

    // View  ===   SEARCH VEHICLE   
    void searchVehicle() {
        int option;
        bool found = false;

        cout << "\n========== SEARCH VEHICLE ==========" << endl;
        cout << "1. Search by Vehicle Number" << endl;
        cout << "2. Search by Vehicle Type" << endl;
        cout << "Enter your choice: ";

        option = getSafeIntInput(1, 2);

        if (option == 1) {
            char vNum[20];
            cout << "\nEnter Vehicle Number: ";
            cin >> vNum;

            for (int i = 0; i < totalVehicles; i++) {
                if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {
                    vehicles[i]->displayInfo();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\n❌ Vehicle not found!" << endl;
            }
        }
        else if (option == 2) {
            char type[20];
            cout << "\nEnter Vehicle Type (Car / Bike / Truck): ";
            cin >> type;

            for (int i = 0; i < totalVehicles; i++) {
                if (strcmp(vehicles[i]->getType(), type) == 0) {
                    vehicles[i]->displayInfo();
                    found = true;
                }
            }

            if (!found) {
                cout << "\n❌ No vehicles found of this type!" << endl;
            }
        }
    }


    void calculateEstimatedCost() {
        char vNumber[20];
        int days;
        bool found = false;

        cout << "\n========== ESTIMATED RENT COST ==========" << endl;

        showAvailableVehicles();

        cout << "\nEnter vehicle number: ";
        cin >> vNumber;

        cout << "Enter number of days: ";
        days = getSafeIntInput(1, 365);

        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), vNumber) == 0) {
                int cost = vehicles[i]->calculateRent(days);

                cout << "\n------ COST ESTIMATION ------" << endl;
                cout << "Vehicle Type : " << vehicles[i]->getType() << endl;
                cout << "Vehicle No   : " << vehicles[i]->getVehicleNumber() << endl;
                cout << "Days         : " << days << endl;
                cout << "Total Cost   : Rs. " << cost << endl;
                cout << "-----------------------------" << endl;

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n❌ Vehicle not found!" << endl;
        }
    }
    
    void addNewVehicle() {
        if (totalVehicles >= 20) {
            cout << "\n❌ Vehicle limit reached!" << endl;
            return;
        }

        int type;
        char vNum[20];
        int rent;

        cout << "\n========== ADD NEW VEHICLE ==========" << endl;
        cout << "1. Car" << endl;
        cout << "2. Bike" << endl;
        cout << "3. Truck" << endl;
        cout << "Select vehicle type: ";

        type = getSafeIntInput(1, 3);

        cout << "Enter Vehicle Number: ";
        cin >> vNum;

        cout << "Enter Rent Per Day: ";
        rent = getSafeIntInput(500, 10000);

        if (type == 1) {
            vehicles[totalVehicles++] = new Car(vNum, rent);
        }
        else if (type == 2) {
            vehicles[totalVehicles++] = new Bike(vNum, rent);
        }
        else if (type == 3) {
            vehicles[totalVehicles++] = new Truck(vNum, rent);
        }

        cout << "\n✅ Vehicle added successfully!" << endl;
    }

  

    void modifyRentRate() {
        char vNum[20];
        int newRent;
        bool found = false;

        cout << "\n========== MODIFY RENT RATE ==========" << endl;

        showAvailableVehicles();

        cout << "\nEnter Vehicle Number: ";
        cin >> vNum;

        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {

                cout << "Current Rent: Rs. " << vehicles[i]->getRentPerDay() << endl;
                cout << "Enter New Rent: ";

                newRent = getSafeIntInput(500, 20000);

                vehicles[i]->setRent(newRent);

                cout << "\n✅ Rent updated successfully!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n❌ Vehicle not found!" << endl;
        }
    }

    void vehicleMaintenanceMenu() {
        char vNum[20];
        int choice;
        bool found = false;

        cout << "\n========== VEHICLE MAINTENANCE ==========" << endl;
        showAvailableVehicles();

        cout << "\nEnter Vehicle Number: ";
        cin >> vNum;

        for (int i = 0; i < totalVehicles; i++) {
            if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {

                cout << "\n1. Mark UNDER MAINTENANCE" << endl;
                cout << "2. Mark AVAILABLE" << endl;
                cout << "Enter choice: ";

                choice = getSafeIntInput(1, 2);

                if (choice == 1) {
                    vehicles[i]->setMaintenance(true);
                    vehicles[i]->setAvailability(false);
                    cout << "\n✅ Vehicle marked UNDER MAINTENANCE" << endl;
                }
                else {
                    vehicles[i]->setMaintenance(false);
                    vehicles[i]->setAvailability(true);
                    cout << "\n✅ Vehicle marked AVAILABLE" << endl;
                }

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n Vehicle not found!" << endl;
        }
    }


    Admin admin;
    void adminMenu() {
        int choice;

        do {
            cout << "\n========== ADMIN PANEL ==========" << endl;
            cout << "1. Add New Vehicle" << endl;
            cout << "2. Modify Rent Rates" << endl;
            cout << "3. Vehicle Maintenance Status" << endl;
            cout << "4. Delete Vehicle (Admin Only)" << endl;
            cout << "5. Reset Password" << endl;
            cout << "6. Logout Admin" << endl;
            cout << "Enter choice: ";

            choice = getSafeIntInput(1, 6);

            switch (choice) {
            case 1:
                addNewVehicle();
                break;
            case 2:
                modifyRentRate();
                break;
            case 3:
                vehicleMaintenanceMenu();
                break;
            case 4:
                // Pass the system's vehicle array to the admin object
                admin.deleteRecord(vehicles, totalVehicles);
                break;
            case 5:
                admin.resetPassword();
                break;
            case 6:
                admin.logout();
                // return to main menu (exit logic handled by while loop condition)
                break;
            }
        } while (choice != 6);

    }

   


    // Main menu
    void displayMenu() {
        int choice;

        do {
            cout << color::Green << "\n________________________________________" << endl;

            cout << "|   VEHICLE RENTAL MANAGEMENT SYSTEM      |" << endl;
            cout << "|_______________________________________|" << endl;
            cout << "|  1. Register Customer                 |" << endl;
            cout << "|  2. Show Available Vehicles           |" << endl;
            cout << "|  3. Rent a Vehicle                    |" << endl;
            cout << "|  4. View Rental History               |" << endl;
            cout << "|  5. Search Vehicle                    |" << endl;
            cout << "|  6. Check Membership Status           |" << endl;
            cout << "|  7. Calculate Estimate Rent           |" << endl;
            cout << "|  8. Return Vehicle                    |" << endl;
            cout << "|  9. Admin Login                       |" << endl;
            cout << "| 10. Invoice Calculation              |" << endl;
            cout << "|  11. Exit                             |" << endl;
            cout << "|_______________________________________|" << endl;
            cout << "Enter your choice: ";

            choice = getSafeIntInput(1, 11);

            switch (choice) {
            case 1: 
                registerCustomer();
                break;
            case 2:
                showAvailableVehicles();
                break;
            case 3:
                rentVehicleMenu();
                break;
            case 4:
                viewRentalHistory();
                break;

            case 5:
                searchVehicle();
                break;
            case 6:
                 // "Check Membership Status" - reusing existing logic check
                 if (strlen(customer.getName()) > 0) {
                     cout << "\nMembership expires on: ";
                     // We need a getter for expiryDate or just call checks
                     if(customer.isMembershipExpired()) cout << "[EXPIRED]";
                     else cout << "[VALID]";
                     cout << endl;
                 } else {
                     cout << "Please register first." << endl;
                 }
                break;
            case 7:
                calculateEstimatedCost();
                break;
            case 8:
                customer.returnVehicle(vehicles, totalVehicles);
                break;
            case 9:
                if (admin.login()) {
                    adminMenu();
                }
                break;
            case 10:
                {
                    double amt1, amt2;
                    cout << "\n--- Operator Overloading Demo ---" << endl;
                    cout << "Enter Car Rent Amount: ";
                    cin >> amt1;
                    cout << "Enter Driver Service Amount: ";
                    cin >> amt2;

                    Invoice inv1(amt1, "Car Rent");
                    Invoice inv2(amt2, "Driver Service");
                    
                    // Combining objects using overloaded '+'
                    Invoice total = inv1 + inv2; 

                    cout << "\n[Invoice 1]";
                    inv1.display();
                    
                    cout << "\n[Invoice 2]";
                    inv2.display();
                    
                    cout << "\n[Combined Invoice (Inv1 + Inv2)]";
                    total.display();
                }
                break;
            case 11:
                cout << "\nThank you for using the Vehicle Rental System!" << endl;
                break;
            }
        } while (choice != 11);
    }

};

// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    RentalSystem system;
    system.displayMenu();
    return 0;
}


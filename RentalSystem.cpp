#include "RentalSystem.h"

// Private method
bool RentalSystem::vehicleExists(const char* vNum) {
    for (int i = 0; i < totalVehicles; i++) {
        if (strcmp(vehicles[i]->getVehicleNumber(), vNum) == 0) {
            return true;
        }
    }
    return false;
}

// Constructor
RentalSystem::RentalSystem() {
    totalVehicles = 0;
    initializeVehicles();
}

// Destructor
RentalSystem::~RentalSystem() {
    for (int i = 0; i < totalVehicles; i++) {
        delete vehicles[i];
    }
}

void RentalSystem::initializeVehicles() {
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

void RentalSystem::registerCustomer() {
    char name[50];
    int typeChoice;
    bool vip = false;

    cout << "\n========== CUSTOMER REGISTRATION ==========" << endl;

    while (true) {
        cout << "Enter your name: ";
       // cin.ignore(100, '\n');   // flush entire buffer
        cin.getline(name, 50);

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

void RentalSystem::showAvailableVehicles() {
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

void RentalSystem::rentVehicleMenu() {
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

void RentalSystem::returnVehicleMenu() {
    if (strlen(customer.getName()) == 0) {
        cout << "\nPlease register first!" << endl;
        return;
    }

    customer.returnVehicle(vehicles, totalVehicles);
    saveToFile();
}

void RentalSystem::saveToFile() {
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

void RentalSystem::viewRentalHistory() {
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

void RentalSystem::searchVehicle() {
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

void RentalSystem::calculateEstimatedCost() {
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

void RentalSystem::addNewVehicle() {
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

void RentalSystem::modifyRentRate() {
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

void RentalSystem::vehicleMaintenanceMenu() {
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

void RentalSystem::adminMenu() {
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

void RentalSystem::displayMenu() {
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
            returnVehicleMenu();
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

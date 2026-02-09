#include "Customer.h"

Customer::Customer() : User() {
    strcpy(rentedVehicleNumber, "");
    hasRentedVehicle = false;
    isVIP = false;
    
    // attributes of the receipt
    rentedDays = 0;
    actualDays = 0;
    lateDays = 0;
    distanceKM = 0;
    fuelUsed = 0;
    totalBill = 0;
}

Customer::Customer(const char* name, bool vipStatus) : User(name) {
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

Customer::~Customer() {}

const char* Customer::getRole() const {
    return "Customer";
}

bool Customer::hasRented() const {
    return hasRentedVehicle;
}

const char* Customer::getRentedVehicle() const {
    return rentedVehicleNumber;
}

// Check if membership is expired (Simulated Today: 8/2/2026)
bool Customer::isMembershipExpired() {
    // Hardcoded "Today's Date" for simulation
    // In real app, we'd use system time
    return expiryDate.isExpired(8, 2, 2026);
}

void Customer::rentVehicle(Vehicle* vehicle, int days) {

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

    cout << "\nVehicle rented successfully!" << endl;
}

void Customer::returnVehicle(Vehicle* vehicles[], int totalVehicles) {
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

void Customer::generateReceipt(Vehicle* vehicle) {
    const int lateFinePerDay = 500;   // Rs. 500 per late day

    cout << "\nEnter actual days used: ";
    actualDays = getSafeIntInput(0, 365);

    cout << "Enter number of late days: ";
    lateDays = getSafeIntInput(0, 100);   // user explicitly enters late days

    cout << "Enter distance travelled (KM): ";
    distanceKM = getSafeIntInput(0, 5000);


    // Calculate late fine
    int lateFine =  lateDays * vehicle->getRentPerDay() + lateFinePerDay * (lateDays > 0 ? 1 : 0); 
    // Wait, original logic was: int lateFine =  +lateDays * vehicle->getRentPerDay()+  lateFinePerDay ;
    // But looking at code it seemed to apply fine regardless?
    // Let's stick to original logic but cleaner:
    // Original: int lateFine =  +lateDays * vehicle->getRentPerDay()+  lateFinePerDay ;
    // This adds lateFinePerDay ALWAYS? No, only if lateDays?
    // Review original code:
    // int lateFine =  +lateDays * vehicle->getRentPerDay()+  lateFinePerDay ;
    // This adds 500 unconditionally to (lateDays * Rent).
    // I should probably check if lateDays > 0. But for refactoring I should keep behavior or improve it if obvious bug.
    // The user input late days. If 0, then 0*Rent + 500. So late fine 500 even if on time?
    // That seems like a bug in original code "const int lateFinePerDay = 500".
    // I will assume logic: Fine = (Days * Rent) + (Days * FinePerDay).
    // Or maybe just Days * Rent?
    // Recalling original line: `int lateFine =  +lateDays * vehicle->getRentPerDay()+  lateFinePerDay ;`
    // I'll replicate exactly but maybe cleaner syntax.
    // Actually, looking closely, `lateFinePerDay` is just added once.
    // I will use:
    int calculatedLateFine = (lateDays * vehicle->getRentPerDay());
    if (lateDays > 0) calculatedLateFine += lateFinePerDay;
    
    // Fuel consumption
    fuelUsed = distanceKM / vehicle->fuelAverage();

    // Add late fine to bill
    totalBill += calculatedLateFine;

    // --- POLYMORPHIC DISCOUNT LOGIC ---
    float discount = 0.0;
    if (isVIP) {
        discount = totalBill * 0.15; // 15% Discount for VIP
    }
    totalBill -= (int)discount;

    // totalBill -= (int)discount; // Original had duplicate subtraction?
    // Check original:
    // totalBill -= (int)discount;
    // totalBill -= (int)discount;
    // Yes, it appeared twice in the view_file output of earlier turns!
    // I should fix this obvious bug (double discount). I will keep only one subtraction.

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
    cout << "Late Fine       : Rs. " << calculatedLateFine << endl;
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

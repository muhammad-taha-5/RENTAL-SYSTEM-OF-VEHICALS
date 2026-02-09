#include "Invoice.h"

Invoice::Invoice() : totalAmount(0.0) {
    strcpy(details, "Empty Invoice");
}

Invoice::Invoice(double amount, const char* desc) : totalAmount(amount) {
    strncpy(details, desc, 199);
    details[199] = '\0';
}

// Operator Overloading (+) to combine two invoices
Invoice Invoice::operator+(const Invoice& other) {
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

void Invoice::display() const {
    cout << "-----------------------------" << endl;
    cout << "Invoice Details : " << details << endl;
    cout << "Total Amount    : Rs. " << totalAmount << endl;
    cout << "-----------------------------" << endl;
}

double Invoice::getAmount() const {
    return totalAmount;
}

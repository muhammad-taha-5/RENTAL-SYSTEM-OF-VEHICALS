#ifndef INVOICE_H
#define INVOICE_H

#include <iostream>
#include <cstring>
#include <cstdio> // for sprintf
using namespace std;

// ============================================
// INVOICE CLASS - Billing Encapsulation & Operator Overloading
// ============================================
class Invoice {
private:
    double totalAmount;
    char details[200]; // Description of charges

public:
    Invoice();
    Invoice(double amount, const char* desc);

    // Operator Overloading (+) to combine two invoices
    Invoice operator+(const Invoice& other);

    void display() const;

    double getAmount() const;
};

#endif // INVOICE_H

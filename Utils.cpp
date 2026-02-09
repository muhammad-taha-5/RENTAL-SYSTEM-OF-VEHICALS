#include "Utils.h"

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

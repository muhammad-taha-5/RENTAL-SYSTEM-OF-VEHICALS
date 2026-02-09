#include"vehical.h"
	// parameterized constructor 
	Vehicle ::Vehicle(double fuelC, double dis_traveled) {
		fuelCapacity = fuelC;
		distanceTravelled = dis_traveled;

	}
	// display 
	void Vehicle::display() {
		cout << "distanceTravelled  " << distanceTravelled << endl;
		cout << "fuelCapacity: " << fuelCapacity << endl;

	}
	   

	car::car(int a, int b, double x, double y) : Vehicle(x, y) {
		maxSpeed = a;
		speed = b;
	}

	// Override the calculateFuelEfficiency() ; 
	double car::calculateFuelEfficiency(double x, double y) {

		if (speed <= maxSpeed) {
			cout << "  Efficiency " << (y / x) + 4 << endl;
			return  (y / x) + 4;
		}
		else {
			cout << "  Efficiency " << (y / x) + 4 << endl;
			return  y / x;

		}
	}

	// display 
	void car::display() {
		cout << "maxSpeed  " << maxSpeed << endl;
		cout << "speed: " << speed << endl;

	}


	truck::truck(int a, double x, double y) : Vehicle(x, y) {
		payLoadCapacity = a;
	}

	// Override the calculateFuelEfficiency() ; 
	double truck::calculateFuelEfficiency(double x, double y) {
		if (payLoadCapacity > 30) {
			cout << "  Efficiency " << (y / x) - 0.07 << endl;
			return  (y / x) - 0.07;
		}
		else {
			cout << "  Efficiency " << (y / x) << endl;
			return  (y / x);
		}
	}

	void truck::display() {
		cout << "payLoadCapacity  " << payLoadCapacity << endl;
	}



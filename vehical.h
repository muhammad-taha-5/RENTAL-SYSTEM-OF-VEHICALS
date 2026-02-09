#include<iostream>
using namespace std;

class Vehicle
{
private:
	double fuelCapacity;
	double distanceTravelled;
public:
	// parameterized constructor 
	Vehicle(double fuelC, double dis_traveled);
	// display 
	void display();
	// this the abstuctionof the data  
	virtual double calculateFuelEfficiency(double x, double y) = 0;

};

// this the pulically driveded class form the base class vehical    

class car :public Vehicle {
private:
	int  maxSpeed;
	int speed;
public:
	// a)	Constructor 

	car(int a, int b, double x, double y);

	// Override the calculateFuelEfficiency() ; 
	double calculateFuelEfficiency(double x, double y);

	// display 
	void display();



};

class truck :public Vehicle {
private:
	int payLoadCapacity;

	// a)	Constructor
public:
	truck(int a, double x, double y);

	// Override the calculateFuelEfficiency() ; 
	double calculateFuelEfficiency(double x, double y);

	void display();


};

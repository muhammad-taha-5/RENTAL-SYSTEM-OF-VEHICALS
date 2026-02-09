#include"vehical.h"

int main() {
	// we could not create any object of the abcstute class ; 
	Vehicle* v;

	car c(5, 6, 7943.45, 43532.5463);
	v = &c;
	v->calculateFuelEfficiency(7943.45 , 43532.5463);
	v->display();



	cout << " =------------------------------- ---------------=  " << endl;
	//  truck ;   
	truck t(6677, 683032.3478, 364832.63649);
	v = &t;
	v->calculateFuelEfficiency(683032.3478, 364832.63649);
	v->display();

	return 0;

}
#include "Planet.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[])
{
	Planet Earth("Earth", 5.97e24,0,0,0);
	Planet Moon("Moon", 7.33e22,3.84e8,0,0);
	Planet Thing("Thing", 3.44e23, 5.97e4, 4.83e6, 0);
	//shows that the force is the same going both ways, but acceleration is not
	/*cout<<"Force of Moon on the Earth: "<<Earth.calcForce(Moon)<<" N"<<endl;
	cout<<"Earth's acceleration due to the moon: "<<Earth.calcAccel()<<" m/s/s"<<endl;
	cout<<"Moon's acceleration due to the Earth: "<<Moon.calcForce(Earth)<<" N"<<endl;
	cout<<"Force of the Earth on the Moon: "<<Moon.calcAccel()<<" m/s/s"<<endl;*/
	
	double dt;
	if (argc == 1) {
		dt = 10;
	} else if (argc == 2) {
		dt = *argv[1];
	} else {
		cout << "Error: invalid number of arguments." << endl;
		return 1;
	}

	for (int i=0; i<10; i++)
	{
		Planet::update(dt);
		cout << "---------------------------------" << endl << endl;
	}

	return 0;
}

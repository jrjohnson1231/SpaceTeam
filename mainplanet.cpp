#include "Planet.h"
#include "iostream"

using namespace std;

int main()
{
	Planet Earth(5.97e24,0,0,0);
	Planet Moon(7.33e22,3.84e8,0,0);
	Planet Thing(3.44e23, 5.97e4, 4.83e6, 0);
	//shows that the force is the same going both ways, but acceleration is not
	/*cout<<"Force of Moon on the Earth: "<<Earth.calcForce(Moon)<<" N"<<endl;
	cout<<"Earth's acceleration due to the moon: "<<Earth.calcAccel()<<" m/s/s"<<endl;
	cout<<"Moon's acceleration due to the Earth: "<<Moon.calcForce(Earth)<<" N"<<endl;
	cout<<"Force of the Earth on the Moon: "<<Moon.calcAccel()<<" m/s/s"<<endl;*/

	for (int i=0; i<10; i++)
	{
		Earth.calcForce();
		Moon.calcForce();
		Thing.calcForce();

		cout << "EARTH" << endl;
		Earth.update(1);
		cout << endl << "MOON" << endl;
		Moon.update(1);
		cout << endl << "THING" << endl;
		Thing.update(1);
		cout << endl << "---------------------------------" << endl << endl;
	}

	return 0;
}

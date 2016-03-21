#include "Planet.hpp"
#include "iostream"

using namespace std;

int main()
{
	Planet Earth(5.97e24,0,0,0);
	Planet Moon(7.33e22,3.84e8,0,0);
	//shows that the force is the same going both ways, but acceleration is not
	cout<<"Force of Moon on the Earth: "<<Earth.calcForce(Moon)<<" N"<<endl;
	cout<<"Earth's acceleration due to the moon: "<<Earth.calcAccel()<<" m/s/s"<<endl;
	cout<<"Moon's acceleration due to the Earth: "<<Moon.calcForce(Earth)<<" N"<<endl;
	cout<<"Force of the Earth on the Moon: "<<Moon.calcAccel()<<" m/s/s"<<endl;
	return 0;
}
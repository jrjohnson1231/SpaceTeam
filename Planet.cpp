#include "Planet.hpp"

Planet::Planet(double m, double a, double b, double c)
{
	mass=m;
	//pos.set(x,y,z);
	x=a;
	y=b;
	z=c;
}

double Planet::calcForce(Planet p)
{
	double G=6.67e-11; 
	//totalForce=(G*mass*p.getMass())/(pos.distance(p.getPos())*pos.distance(p.getPos()));
	totalForce=(G*mass*p.getMass())/(distance(p)*distance(p));
	return totalForce;
}

double Planet::calcAccel()
{
	accel= totalForce/mass;
	return accel;
}

double Planet::getMass()
{
	return mass;
}

double Planet::distance(Planet p)
{
	return sqrt((x-p.getx())*(x-p.getx())+(y-p.gety())*(y-p.gety())+(z-p.getz())*(z-p.getz()));
}

/*Tensor Planet::getPos()
{
	return pos;
}*/

double Planet::getx()
{
	return x;
}

double Planet::gety()
{
	return y;
}

double Planet::getz()
{
	return z;
}
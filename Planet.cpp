#include "Planet.hpp"

Planet::Planet(double m, double x, double y, double z)
{
	mass=m;
	pos.set(x,y,z);
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
	return sqrt((pos.getx()-p.getx())*(pos.getx()-p.getx())+(pos.gety()-p.gety())*(pos.gety()-p.gety())+(pos.getz()-p.getz())*(pos.getz()-p.getz()));
}

/*Tensor Planet::getPos()
{
	return pos;
}*/

double Planet::getx()
{
	return pos.getx();
}

double Planet::gety()
{
	return pos.gety();
}

double Planet::getz()
{
	return pos.getz();
}
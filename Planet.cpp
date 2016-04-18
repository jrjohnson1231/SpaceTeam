#include "Planet.h"

#define DEBUG 1 

// static vector of all planets
vector<Planet *> Planet::planets;

//constructor
Planet::Planet(string n, double m, double x, double y, double z) : Body(n, m, x, y, z)
{
	mass = m;
	pos.set(x,y,z);
	planets.push_back(this);
}

//calculate the force
void Planet::calcForce()//gravitational force
{
	double G=6.67e-11;
	totalForce.clear();

	for (int i = 0; i < planets.size(); i++) 
	{
		// don't add force if it is with itself
		if (planets[i] != this) 
		{
			Tensor r = planets[i]->pos - pos;
			totalForce = totalForce + r*((G*mass*planets[i]->mass)/(r.getr()*r.getr()*r.getr()));
		}
	}

	accel = totalForce / mass;
}

void Planet::update(double dt)
{
	// calculate force for each planet
	for (int i = 0; i < planets.size(); i++) 
	{
		planets[i]->calcForce();

		if (DEBUG) cout << planets[i]->name << ":" << endl << planets[i]->pos << endl;
	}

	for (int i = 0; i < planets.size(); i++) 
	{
		planets[i]->pos = planets[i]->pos + (planets[i]->vel*dt);
		planets[i]->vel = planets[i]->vel + (planets[i]->accel*dt);
	}
}


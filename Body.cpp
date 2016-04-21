#include "Body.h"

#define DEBUG 1 

// static vector of all bodies
//vector<Body *> Body::bodies;

//constructor
Body::Body(string name, double m, double x, double y, double z) : name(name)
{
	mass = m;
	pos.set(x,y,z);
}

double Body::getMass()
{
	return mass;
}

double Body::getx()
{
	return pos.getx();
}

double Body::gety()
{
	return pos.gety();
}

double Body::getz()
{
	return pos.getz();
}

//moves the bodies according to the force
/*void Body::update(double dt)
{
	// calculate force for each planet
	for (int i = 0; i < bodies.size(); i++) 
	{
		bodies[i]->calcForce();

		if (DEBUG) cout << bodies[i]->name << ":" << endl << bodies[i]->pos << endl;
	}
	
	for (int i = 0; i < bodies.size(); i++) 
	{
		bodies[i]->pos = bodies[i]->pos + (bodies[i]->vel*dt);
		bodies[i]->vel = bodies[i]->vel + (bodies[i]->accel*dt);
	}
}*/

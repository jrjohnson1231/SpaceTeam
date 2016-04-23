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

/* Constructor */
Body::Body(string name, string imagename, double mass, Tensor p, Tensor v) : name(name), imagename(imagename), mass(mass) {
	// Set position and velocity
	pos = p;
	vel = v;

	// Load image
	SDL_Surface* image = IMG_Load(imagename.c_str());
	if (image == NULL) {
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}

	image = SDL_DisplayFormat(image);
}
	

double Body::getMass()
{
	return mass;
}

Tensor Body::getPos() {
	return pos;
}

Tensor Body::getVel() {
	return vel;
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

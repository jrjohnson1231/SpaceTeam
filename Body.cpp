#include "Body.h"

#define DEBUG 1

// static vector of all bodies
vector<Body *> Body::bodies;

//constructor
Body::Body(string name, double m, double x, double y, double z) : name(name)
{
	mass = m;
	pos.set(x,y,z);
}

/* Constructor */
Body::Body(string name, string imagename) : name(name), imagename(imagename) {
	// Load image
	SDL_Surface* loadedimage = IMG_Load(imagename.c_str());
	if (loadedimage == NULL) {
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}

	image = SDL_DisplayFormat(loadedimage);
	if (image == NULL) {
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}
	
	
}

/* Constructor */
Body::Body(string name) : name(name) {
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

bool Body::display(SDL_Surface *screen, Tensor topleft, Tensor botright, int height, int width){
	//Blit Image
	//offset.x = getx(topleft,botright,height,width);
	//offset.y = gety(topleft)
	offset.x = pos.x;
	offset.y = pos.y;
	cout << "Displaying " << name << endl;
	//cout << "(" << offset.x << "," << offset.y << ")" << endl;
	//cout << "(" << pos.x << "," << pos.y << ")" << endl;
	if (SDL_BlitSurface(image, NULL, screen, &offset) != 0) {
		cout << "Error: " << SDL_GetError() << endl;
	}
	return 0;
}

int Body::getx(Tensor topleft,Tensor botright, int height, int width){
	double numer = pos.getx() - topleft.getx();
	double denom = botright.getx() - topleft.getx();
	return (numer/denom * height);
}
int Body::gety(Tensor topleft,Tensor botright, int height, int width){
	double numer = pos.gety() - topleft.gety();
	double denom = botright.gety() - topleft.gety();
	return numer/denom * width;
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

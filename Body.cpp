#include "Body.h"

#define DEBUG 1

// static vector of all bodies and static center of mass
vector<Body *> Body::bodies;
Tensor Body::COM;
double Body::xscale = 0;
double Body::yscale = 0;

//constructor
Body::Body(string name, double m, double x, double y, double z) : name(name)
{
	mass = m;
	pos.set(x,y,z);
}

// Constructor 
//takes in planet name, image name
//opens image and if the image doesn't work, the user is notified 
Body::Body(string name, string imagename) : name(name), imagename(imagename)
{
	// Load image
	/*if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Error initializing SDL:" << endl << SDL_GetError() << endl;
	}*/
	image = NULL;
	image = IMG_Load(imagename.c_str());
	if (image == NULL)
	{
		cerr << "ERROR: image load failed. " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	//Set black of image as transparent
	Uint32 colorkey = SDL_MapRGB(image->format, 0,0,0);
	SDL_SetColorKey(image,SDL_SRCCOLORKEY,colorkey);

	// if failed, print error message
	if (image == NULL)
	{
		cerr << "ERROR: image load failed. " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	
	if (DEBUG) cerr << "Made " << name << endl;
}

// Constructor
Body::Body(string name) : name(name) 
{
}

//getters

double Body::getMass()
{
	return mass;
}

Tensor Body::getPos() 
{
	return pos;
}

Tensor Body::getVel() 
{
	return vel;
}

//displays the body object
bool Body::display(SDL_Surface *screen)
{
	//Blit Image
	SDL_Rect offset;
	offset.x = (pos.x-COM.x)/xscale + screen->w/2 - image->w/2;
	offset.y = (pos.y-COM.y)/yscale + screen->h/2 - image->h/2;
	if (DEBUG)
	{
		cerr << "Displaying " << name << endl;
		cerr << "(" << offset.x << "," << offset.y << ")" << endl;
	}
	if (SDL_BlitSurface(image, NULL, screen, &offset) != 0) {
		cerr << "Error displaying object:" << endl << SDL_GetError() << endl;
		return false;
	}
	return true;
}

//returns x position on screen
void Body::xRange(double &min, double &max)
{
	min = COM.x;
	max = COM.x;
	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->pos.x < min) min = bodies[i]->pos.x;
		if (bodies[i]->pos.x > max) max = bodies[i]->pos.x;
	}
}

//returns y position on screen
void Body::yRange(double &min, double &max)
{
	min = COM.y;
	max = COM.y;
	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->pos.y < min) min = bodies[i]->pos.y;
		if (bodies[i]->pos.y > max) max = bodies[i]->pos.y;
	}
}

/* Calculates center of mass of all bodies */
void Body::calcCOM()
{
	double totalMass = 0;
	Tensor averageX(0, 0, 0);
	for (int i = 0; i < bodies.size(); i++)
	{
		totalMass += bodies[i]->mass;
		averageX = averageX + bodies[i]->pos * bodies[i]->mass;
	}
	COM = averageX / totalMass;
}

void Body::calcScale(SDL_Surface *screen)
{
	double xmax = 0;
	double ymax = 0;
	for (int i = 0; i < bodies.size(); i++)
	{
		if (abs(bodies[i]->pos.x - COM.x) > xmax) xmax = abs(bodies[i]->pos.x);
		if (abs(bodies[i]->pos.y - COM.y) > ymax) ymax = abs(bodies[i]->pos.y);
		cout << xmax << endl;
	}

	if (xmax >= ymax) {
		xscale = xmax * 3 / screen->w;
		yscale = xmax * 3 / screen->h;
	}
	else {
		xscale = ymax / 3 / screen->w;
		yscale = ymax / 3 / screen->h;
	}

	if (DEBUG) cout << "xscale: " << xscale << " yscale: " << yscale << endl;
}

#include "Body.h"

#define DEBUG 1

// static vector of all bodies and static center of mass
vector<Body *> Body::bodies;
Tensor Body::COM;

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
	SDL_Surface *loadedimage = NULL;
	image = IMG_Load(imagename.c_str());
	if (image == NULL)
	{
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}

	// Set image to display format
	//SDL_Surface *temp = SDL_DisplayFormat(loadedimage);
	//image = loadedimage;
	//Set black of image as transparent
	Uint32 colorkey = SDL_MapRGB(image->format, 0,0,0);
	SDL_SetColorKey(image,SDL_SRCCOLORKEY,colorkey);

	// if failed, print error message
	if (image == NULL)
	{
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}
	
	//SDL_FreeSurface(loadedimage);
	
	if (DEBUG) cout << "Made " << name << endl;
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
	offset.x = pos.x/20e5 + screen->w/2 - 5;
	offset.y = pos.y/20e5 + screen->h/2 - 5;
	offset.w = 10;
	offset.h = 10;
	cout << "Displaying " << name << endl;
	cout << "(" << offset.x << "," << offset.y << ")" << endl;
	//cout << "(" << pos.x << "," << pos.y << ")" << endl;
	if (SDL_BlitSurface(image, NULL, screen, &offset) != 0) {
		cout << "Error displaying object:" << endl << SDL_GetError() << endl;
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
	cout << "COM: " << COM;
}

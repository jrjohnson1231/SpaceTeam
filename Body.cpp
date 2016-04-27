#include "Body.h"

/* ----- STATIC MEMBERS ----- */

// Static vector of all bodies
vector<Body *> Body::bodies;

// Static tensor with initial center of mass
Tensor Body::COM;

// Static doubles for window scaling in each direction
double Body::xscale = 0;
double Body::yscale = 0;


/* ----- CONSTRUCTORS ----- */

/* Used to initialize name of planet and to initialize SDL image
 * Terminates program if image does not load to avoid segmentation fault */
Body::Body(string name, string imagename) : name(name), imagename(imagename)
{
	// Attempt to load image
	image = NULL;
	image = IMG_Load(imagename.c_str());
	if (image == NULL) // catch failed load
	{
		cerr << "ERROR: image load failed. " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1); // quit on error
	}

	// Set black of image as transparent
	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0, 0);
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
}


/* ----- DESTRUCTORS ----- */
Body::~Body() {}


/* ----- GET FUNCTIONS ----- */

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


/* ----- MEMBER FUNCTIONS ----- */

/* Blits picture of planet onto screen
 * Takes SDL_Surface* to print images two as parameter
 * Returns false if there is an error displaying it, true otherwise */
bool Body::display(SDL_Surface *screen)
{
	// Calculate image coordinates
	SDL_Rect offset;
	offset.x = (pos.x - COM.x)/xscale + screen->w/2 - image->w/2;
	offset.y = (pos.y - COM.y)/yscale + screen->h/2 - image->h/2;

	// Debugging messages
	if (DEBUG)
	{
		cerr << "Displaying " << name << endl;
		cerr << "(" << offset.x << "," << offset.y << ")" << endl;
	}

	// Blit image to screen
	if (SDL_BlitSurface(image, NULL, screen, &offset) != 0) // Error displaying image
	{
		cerr << "Error displaying object:" << endl << SDL_GetError() << endl;
		return false;
	}
	return true;
}


/* ----- STATIC FUNCTIONS ----- */

/* Calculates center of mass of all bodies */
void Body::calcCOM()
{
	double totalMass = 0;
	Tensor averageX(0, 0, 0);

	// Sum all masses and mass weighted positions
	for (int i = 0; i < bodies.size(); i++)
	{
		totalMass += bodies[i]->mass;
		averageX = averageX + bodies[i]->pos * bodies[i]->mass;
	}

	// Divide mass weighted position sum by total mass to get center of mass
	COM = averageX / totalMass;

	// Debugging message
	if (DEBUG) cerr << "Center of mass: " << COM;
}

/* Calculate the scale to print the bodies at
 * Takes SDL_Surface* bodies will be printed on as a parameter */
void Body::calcScale(SDL_Surface *screen)
{
	// Find furthest distance from center of mass in each direction
	double xmax = 0;
	double ymax = 0;
	for (int i = 0; i < bodies.size(); i++)
	{
		if (abs(bodies[i]->pos.x - COM.x) > xmax) xmax = abs(bodies[i]->pos.x - COM.x);
		if (abs(bodies[i]->pos.y - COM.y) > ymax) ymax = abs(bodies[i]->pos.y - COM.y);
	}

	// Scale based on the longest distance
	// A coordinate at the max appears 1/3 screens from the center of mass in that direction
	if (xmax >= ymax)
	{
		xscale = xmax * 3 / screen->w;
		yscale = xmax * 3 / screen->h;
	}
	else
	{
		xscale = ymax * 3 / screen->w;
		yscale = ymax * 3 / screen->h;
	}

	// Debugging message
	if (DEBUG) cerr << "xscale: " << xscale << " yscale: " << yscale << endl;
}

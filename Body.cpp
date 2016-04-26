#include "Body.h"

#define DEBUG 1

// static vector of all bodies
vector<Body *> Body::bodies;

/*//constructor
Body::Body(string name, double m, double x, double y, double z) : name(name)
{
	mass = m;
	pos.set(x,y,z);
}*/

// Constructor 
//takes in planet name, image name
//opens image and if the image doesn't work, the user is notified 
Body::Body(string name, string imagename) : name(name), imagename(imagename)
{
	// Load image
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Error initializing SDL:" << endl << SDL_GetError() << endl;
	}
	SDL_Surface* loadedimage = IMG_Load(imagename.c_str());
	if (loadedimage == NULL)
	{
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}
	// Set image to display format
	image = SDL_DisplayFormat(loadedimage);
	//Set black of image as transparent
	//Uint32 colorkey = SDL_MapRGB(image->format, 0,0,0);
	//SDL_SetColorKey(image,SDL_SRCCOLORKEY,colorkey);
	// if failed, print error message
	if (image == NULL)
	{
		cout << "ERROR: image load failed. " << SDL_GetError() << endl;
		return;
	}
	
	SDL_FreeSurface(loadedimage);
	
	
}

/* Constructor
Body::Body(string name) : name(name) 
{
}*/

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
bool Body::display(SDL_Surface *screen, Tensor topleft, Tensor botright, int height, int width)
{
	//Blit Image
	//offset.x = getx(topleft,botright,height,width);
	//offset.y = gety(topleft,botright,height,width);
	offset.x = pos.x/20e5 + + screen->w/2 - 5;
	offset.y = pos.y/20e5 + + screen->h/2 - 5;
	offset.w = 10;
	offset.h = 10;
	cout << "Displaying " << name << endl;
	cout << "(" << offset.x << "," << offset.y << ")" << endl;
	//cout << "(" << pos.x << "," << pos.y << ")" << endl;
	if (SDL_BlitSurface(image, NULL, screen, &offset) != 0) {
		cout << "Error displaying object:" << endl << SDL_GetError() << endl;
	}
	return 0;
}

//returns x position on screen
int Body::getx(Tensor topleft,Tensor botright, int height, int width)
{
	double numer = pos.getx() - topleft.getx();
	double denom = botright.getx() - topleft.getx();
	return (numer/denom * height);
}

//returns y position on screen
int Body::gety(Tensor topleft,Tensor botright, int height, int width)
{
	double numer = pos.gety() - topleft.gety();
	double denom = botright.gety() - topleft.gety();
	return numer/denom * width;
}
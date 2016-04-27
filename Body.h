#ifndef BODY_HPP
#define BODY_HPP

#ifndef DEBUG
#define DEBUG 0
#endif

#include "Tensor.h" // math vector class
#include <cmath> // abs(), sqrt()
#include <iostream> // cout, cerr
#include <vector> // vector
#include <string> // string
#include <fstream> // filestream
#include <cstdlib> // exit
#include <SDL/SDL.h> // graphics libraries
#undef main // SDL has it's own main which conflicts during linking
#include <SDL_image/SDL_image.h> // graphic image libraries
using namespace std;

/* This is an abstract class for different types of bodies.
/* When given an SDL_Surface its derived object will display itself
/* Performs calculations to get center of mass and scaling based on screen and body sizes */

class Body
{
	friend class Window;

	public:
		// Constructors
		Body(string name, string imagename);

		// Get Functions
		double getMass();
		Tensor getPos();
		Tensor getVel();

		// Member Functions
		bool display(SDL_Surface *); // Displays body onto SDL_Surface *

		// Pure Virtual Functions
		virtual void calcForce() = 0; // Calculate total force on an object

		// Static Functions
		static void calcCOM(); // Calculates center of mass of all bodies
		static void calcScale(SDL_Surface *); // Calculates the scale at which to display all bodies

		// Static Members (public)
		static vector<Body *> bodies; // Contains pointer to each object
	
	protected:
		// Object variables
		double mass; // Mass of object
		double rad; // Radius of object
		string name; // Name to identify object
		string imagename; // Relative path to the image for the object

		// SDL variables
		SDL_Surface *image; // SDL_Surface of the image

		// Object vectors
		Tensor accel; // Acceleration vector
		Tensor totalForce; // Force vector
		Tensor pos; // Position vector
		Tensor vel; // Velocity vector

		// Static variables
		static Tensor COM; // Initial center of mass of the system
		static double xscale; // Scale to display planets in x-direction
		static double yscale; // Scale to display planets in y-direction
};

#endif

#ifndef PLANET_H
#define PLANET_H

#ifndef DEBUG
#define DEBUG 0
#endif

#include "Tensor.h" // math vector class
#include "Body.h" // parent class
#include <iostream> // cout, cerr
#include <vector> // vector
#include <string> // string
#include <functional> // reference_wrapper
#include <cmath> // sqrt, exp
using namespace std;

/* This is a derived Body class for planets
 * Uses the Newton's Law of Gravitation between bodies */

class Planet: public Body
{
	public:
		// Constructors
		Planet(string name, string imagename, double m=9.1e-31, double r=0, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		
		// Destructors
		~Planet();

		// Member functions
		void calcForce(); // Calculate the force for a body
		
		// Static functions
		static void update(double); // Update new pos, vel, accell for all 

	private:
		// Helper functions
		void removePtr(); // Deletes pointer to body from charges vector
		static void collide(); // Decides if two charged particles have collided

		// Static variables
		static vector<reference_wrapper<Planet> > planets; // constains pointer to each object
};

#endif

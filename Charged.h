#ifndef CHARGEDPARTICLE_H
#define CHARGEDPARTICLE_H

#include "Tensor.h" // math vector class
#include "Body.h" // parent class
#include <iostream> // cout, cerr
#include <vector> // vector
#include <string> // string
#include <functional> // reference_wrapper
#include <cmath> // sqrt, exp
using namespace std;

/* This is a derived Body class for charged particles
/* Uses the Coulomb Law between bodies */

class Charged: public Body
{
	public:
		// Constructors
		Charged(string name, string imagename, double m=9.1e-31, double q=1.6e-19, double r=0, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);

		// Get functions
		double getCharge();
		
		// Member functions
		void calcForce(); // Calculate the force for a body
		
		// Static functions
		static void update(double); // Update new pos, vel, accell for all bodies

	private:
		// Helper functions
		void removePtr();//deletes pointer to body from charges vector
		static void collide();//decides if two charged particles have collided

		// Object variables
		double charge;

		// Static variables
		static vector<reference_wrapper<Charged> > charges; // constains pointer to each object
};

#endif

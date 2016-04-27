#include "Charged.h"

/* ----- STATIC MEMBERS ----- */

// Vector with references to each object
vector<reference_wrapper<Charged> > Charged::charges;


/* ----- CONSTRUCTORS ----- */

/* Initializes all member variables and Parent class */
Charged::Charged(string name, string imagename, double m, double q, double r, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename)
{
	// Initialize variables
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	charge = q;
	mass = m;
	rad = r;

	// Add object to vectors
	charges.push_back(*this);
	bodies.push_back(&charges.back().get());

	// Recalculate center of mass
	Body::calcCOM();

	// Debugging message	
	if (DEBUG) cerr << "Made " << name << " at " << pos << endl;
}


/* ----- DESTRUCTORS ----- */
Charged::~Charged() {}


/* ----- GET FUNCTIONS ----- */

double Charged::getCharge()
{
	return charge;
}


/* ----- MEMBER FUNCTIONS ----- */

/* Calculates force on an object using Coulomb Force
 * F = k*q1*q2/r^2 */
void Charged::calcForce()
{
	double k= 8.99e9; // Coulomb constant
	totalForce.clear(); // Set force to 0

	// Loop over all bodies and add to the total force
	for (int i = 0; i < charges.size(); i++)
	{
		if (&charges[i].get() != this) // Ignore force with itself
		{
			// Vector between objects
			Tensor r = charges[i].get().pos-pos;

			// Force between objects
			totalForce=totalForce+r*((k*charge*charges[i].get().charge)/(r.getr()*r.getr()*r.getr()));
		}
	}

	// Get total accelleration from force (F = ma)
	accel=totalForce/mass;
}


/* ----- STATIC FUNCTIONS ----- */

/* Determines if two bodies have collided
 * Destroys planets if they collide */
void Charged::collide()
{
	if (charges.size()==1) return; // No collisions if there is one body

	// Iterate over all charge pairs and look for collisions
	for (int i = 0; i < charges.size(); i++)
	{
		for (int j = 0; j < charges.size(); j++)
		{
			if (i==j) continue; // Don't compare with itself
			else
			{
				// Vector between objects
				Tensor r = charges[i].get().pos - charges[j].get().pos;

				// Check if they are too close
				if (r.getr() <= charges[i].get().rad + charges[j].get().rad)
				{
					// Debugging message
					if (DEBUG) cerr << charges[i].get().name << " and " << charges[j].get().name << " collided " << endl;

					// Remove from bodies
					charges[i].get().removePtr();
					charges[j].get().removePtr();

					// Remove from charges
					charges.erase(charges.begin() + i);
					charges.erase(charges.begin() + j-1);

					return;
				}
			}
		}
	}

}

/* Updates all the bodies based on Verlet Integration
 * Verlet Integration uses velocity halfway through dt interval for better approximation */
void Charged::update(double dt)
{
	// Debugging message
	if (DEBUG) {cerr << endl << "There are " << charges.size() << " charges" << endl;}

	// Check for collisions
	collide();

	// Calculate force for each planet at initial velocity
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().calcForce();
	}

	// Calculate halfway velocity and use it to get final position
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().vel = charges[i].get().vel + charges[i].get().accel*dt/2;
		charges[i].get().pos = charges[i].get().pos + charges[i].get().vel*dt;
	}

	// Calculate new force
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().calcForce();
		
		// Debugging message
		if (DEBUG) cerr << charges[i].get().name << ":" << endl << charges[i].get().pos << endl << charges[i].get().accel << endl;
	}

	// Calculate new velocity based one new Force
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().vel = charges[i].get().vel + charges[i].get().accel*dt/2;
	}
}


/* ----- HELPER FUNCTIONS ----- */

/* Removes pointer when body vector when charges collide
 * Ensures they are removed from both charges and bodies vectors */
void Charged::removePtr()
{
	// find itself in the body vector and removes it
	for (int i = 0; i < bodies.size(); i++) {
		if (bodies[i] == this)
		{
			bodies.erase(bodies.begin() + i);
		}
	}

	// Debugging message
	if (DEBUG) {
		cerr << "Removing " << name << " pointer" << endl;
	}
}
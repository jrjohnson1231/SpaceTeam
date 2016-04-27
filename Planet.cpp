#include "Planet.h"

/* ----- STATIC MEMBERS ----- */

// vector with references to each object
vector<reference_wrapper<Planet> > Planet::planets;

/* ----- CONSTRUCTORS ----- */

/* Initializes all member variables and Parent class */
Planet::Planet(string name, string imagename, double m, double r, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename) 
{
	// Initialize variables
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	mass = m;
	rad=r;

	// Add object to vectors
	planets.push_back(*this);
	bodies.push_back(&(planets.back().get()));

	// Recalculate center of mass
	Body::calcCOM();
}


/* ----- MEMBER FUNCTIONS ----- */

/* Calculates force on an object using Coulomb Force
/* F = G*m1*m2/r^2 */
void Planet::calcForce()
{
	double G=6.67e-11; // Gravitational constant
	totalForce.clear(); // Set force to 0

	// Loop over all bodies and add to the total fofce
	for (int i = 0; i < planets.size(); i++)
	{
		if (&planets[i].get() != this) // Ignore force with itself
		{
			// Vector between objects
			Tensor r = planets[i].get().pos - pos;

			// Force between objecs
			totalForce = totalForce + r*((G*mass*planets[i].get().mass)/(r.getr()*r.getr()*r.getr()));
		}
	}

	// Get total accelleration from force (F = ma)
	accel = totalForce / mass;
}


/* ----- STATIC FUNCTIONS ----- */

/* Determines if two bodies have collided
/* Destroys planets if they collide */
void Planet::collide()
{
	if (planets.size()==1) return; // No collisions if there is one body

	// Iterate over all charge pairs and look for collisions
	for (int i = 0; i < planets.size(); i++)
	{
		for (int j = 0; j < planets.size(); j++)
		{
			if (i==j) continue; // Don't compare with itself
			else
			{
				// Vector between objects
				Tensor r = planets[i].get().pos - planets[j].get().pos;

				// Check if they are too close
				if (r.getr() <= planets[i].get().rad + planets[j].get().rad)
				{
					// Debugging message
					if (DEBUG) cerr << planets[i].get().name << " and " << planets[j].get().name << " collided " << endl;

					// Remove from bodies
					planets[i].get().removePtr();
					planets[j].get().removePtr();

					// Remove from planets
					planets.erase(planets.begin() + i);
					planets.erase(planets.begin() + j-1);

					return;
				}
			}
		}
	}

}

/* Updates all the bodies based on Verlet Integration
/* Verlet Integration uses velocity halfway through dt interval for better approximation */
void Planet::update(double dt)
{
	// Debugging message
	if (DEBUG) {cerr << endl << "There are " << planets.size() << " planets" << endl;}

	// Check for collisions
	collide();

	// Calculate force for each planet at initial velocity
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().calcForce();
	}

	// Calculate halfway velocity and use it to get final position
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().vel = planets[i].get().vel + planets[i].get().accel*dt/2;
		planets[i].get().pos = planets[i].get().pos + planets[i].get().vel*dt;
	}

	// Calculate new force
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().calcForce();
		
		// Debugging message
		if (DEBUG) cerr << planets[i].get().name << ":" << endl << planets[i].get().pos << endl << planets[i].get().accel << endl;
	}

	// Calculate new velocity based one new Force
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().vel = planets[i].get().vel + planets[i].get().accel*dt/2;
	}
}


/* ----- HELPER FUNCTIONS ----- */

/* Removes pointer when body vector when planets collide
/* Ensures they are removed from both planets and bodies vectors */
void Planet::removePtr()
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
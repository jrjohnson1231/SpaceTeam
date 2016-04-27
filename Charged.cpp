#include "Charged.h"

#define DEBUG 1

vector<reference_wrapper<Charged> > Charged::charges;

//constructors
Charged::Charged(string name, string imagename, double m, double q, double r, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename)
{
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	charge = q;
	mass = m;
	rad = r;
	charges.push_back(*this);
	bodies.push_back(&charges.back().get());

	Body::calcCOM();
}

//destructor
void Charged::removePtr()
{
	// find itself in the body vector and removes it
	for (int i = 0; i < bodies.size(); i++) {
		if (bodies[i] == this)
		{
			bodies.erase(bodies.begin() + i);
		}
	}
	if (DEBUG) {
		cerr << "Removing " << name << " pointer" << endl;
	}
}

void Charged::calcForce()//coulomb force
{
	double k= 8.99e9; //coulomb force constant
	totalForce.clear();

	for (int i = 0; i < charges.size(); i++)
	{
		if (&charges[i].get() != this)
		{
			Tensor r = charges[i].get().pos-pos;
			totalForce=totalForce+r*((k*charge*charges[i].get().charge)/(r.getr()*r.getr()*r.getr()));
		}
	}

	accel=totalForce/mass;
}

// determines whether or not two planets have collided
void Charged::collide()
{
	if (charges.size()==1){return;}
	int eraseStatus=0;
	for (int i = 0; i < charges.size(); i++)
	{
		for (int j = 0; j < charges.size(); j++)
		{
			if (i==j) {continue;}
			else {
				Tensor r = charges[i].get().pos - charges[j].get().pos;
				if (r.getr() <= charges[i].get().rad + charges[j].get().rad) {
					if (DEBUG) cerr << charges[i].get().name << " and " << charges[j].get().name << " collided " << endl;
					charges[i].get().removePtr();
					charges[j].get().removePtr();
					charges.erase(charges.begin() + i);
					charges.erase(charges.begin() + j-1);

					eraseStatus=1;
					return;
				}
			}

		}
		if (eraseStatus==1){break;}
	}

}

double Charged::getCharge()
{
	return charge;
}

void Charged::update(double dt)
{
	if (DEBUG) {cerr << endl << "There are " << charges.size() << " charges" << endl;}
	// Check for collisions
	collide();
	// calculate force for each planet at initial velocity
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().calcForce();
	}
	// calculate halfway velocity and use it to get position
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().vel = charges[i].get().vel + charges[i].get().accel*dt/2;
		charges[i].get().pos = charges[i].get().pos + charges[i].get().vel*dt;
	}
	// calculate new force
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().calcForce();
		
		// display some debugging info
		if (DEBUG) cerr << charges[i].get().name << ":" << endl << charges[i].get().pos << endl << charges[i].get().accel << endl;
	}
	// calculate new velocity based one new force
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().vel = charges[i].get().vel + charges[i].get().accel*dt/2;
	}
}

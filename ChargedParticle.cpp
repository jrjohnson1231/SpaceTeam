#include "ChargedParticle.hpp"

#define DEBUG 1

vector<Charged *> Charged::charges;

//constructor
Charged::Charged(string n, double m, double x, double y, double z, double c) : Body(n, m, x, y, z)
{
	name=n;
	charge=c;
	mass= m;
	pos.set(x,y,z);
	charges.push_back(this);
}

void Charged::calcForce()//coulomb force
{
	double k= 8.99e9; //coulomb force constant
	totalForce.clear();

	for (int i=0; i<charges.size(); i++)
	{
		if (charges[i] != this)
		{
			Tensor r = charges[i]->pos-pos;
			totalForce=totalForce+r*((k*charge*charges[i]->charge)/(r.getr()*r.getr()*r.getr()));
		}
	}
	accel=totalForce/mass;
}

double Charged::getCharge()
{
	return charge;
}

void Charged::update(double dt)
{
	// calculate force for each planet
	for (int i = 0; i < charges.size(); i++) {
		charges[i]->calcForce();

		if (DEBUG) cout << charges[i]->name << ":" << endl << charges[i]->pos << endl;
	}
	
	for (int i = 0; i < charges.size(); i++) {
		charges[i]->pos = charges[i]->pos + (charges[i]->vel*dt);
		charges[i]->vel = charges[i]->vel + (charges[i]->accel*dt);
	}
}

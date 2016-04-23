#include "ChargedParticle.h"

#define DEBUG 1

vector<Charged > Charged::charges;

//constructor
Charged::Charged(string n, double m, double x, double y, double z, double c) : Body(n, m, x, y, z)
{
	name=n;
	charge=c;
	mass= m;
	pos.set(x,y,z);
	charges.push_back(*this);
}

//destructor
Charged::~Charged() {
	// find itself in the body vector and removes it
	for (i = 0; i < elements.size(); i++) {
		if (bodies[i] == this) {
			bodies.erase(bodies.begin() + i);
		}
	}
}

void Charged::calcForce()//coulomb force
{
	double k= 8.99e9; //coulomb force constant
	totalForce.clear();

	for (int i=0; i<charges.size(); i++)
	{
		if (&charges[i] != this)
		{
			Tensor r = charges[i].pos-pos;
			totalForce=totalForce+r*((k*charge*charges[i].charge)/(r.getr()*r.getr()*r.getr()));
		}
	}
	accel=totalForce/mass;
}

double Charged::getCharge()
{
	return charge;
}

void Charged::collide()
{
	if (charges.size()==1){return;}
	int eraseStatus=0;
	cout<<charges.size()<<endl;
	for (int i = 0; i < charges.size(); ++i)
	{
		for (int j = 0; i < charges.size(); ++j)
		{
			if (i==j) {continue;}
			else if((charges[i].pos.getx()-charges[j].pos.getx()<=.1)&&(charges[i].pos.gety()-charges[j].pos.gety()<=.1)&&(charges[i].pos.getz()-charges[j].pos.getz()<=.1))
			{
				cout<<charges[i].name<<charges[j].name<<endl;
				charges.erase (charges.begin()+i);
				cout<<charges.size();
				cout<<charges[j].name<<endl;
				charges.erase (charges.begin()+(j-1));
				eraseStatus=1;
				return;
			}

		}
		if (eraseStatus==1){break;}
	}

}

void Charged::update(double dt)
{
	// calculate force for each planet
	for (int i = 0; i < charges.size(); i++) {
		charges[i].calcForce();

		if (DEBUG) cout << charges[i].name << ":" << endl << charges[i].pos << endl;
	}
	
	for (int i = 0; i < charges.size(); i++) {
		charges[i].pos = charges[i].pos + (charges[i].vel*dt);
		charges[i].vel = charges[i].vel + (charges[i].accel*dt);
	}
	collide();
}

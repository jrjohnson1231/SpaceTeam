#include "Charged.h"

#define DEBUG 1

vector<reference_wrapper<Charged> > Charged::charges;

//constructors
Charged::Charged(string name, string imagename, double m, double q, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename)
{
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	charge = q;
	mass = m;
	charges.push_back(*this);
	bodies.push_back(&charges.back().get());
}

/*Charged::Charged(string name, double m, double q, double x, double y, double z, double vx, double vy, double vz) : Body(name)
{
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	charge = q;
	mass = m;
	charges.push_back(*this);
	bodies.push_back(this);
}*/

//destructor
void Charged::removePtr() {
	// find itself in the body vector and removes it
	for (int i = 0; i < bodies.size(); i++) {
		if (bodies[i] == this) {
			bodies.erase(bodies.begin() + i);
		}
	}
	if (DEBUG) {
		cerr << "Removing " << name << " pointer" << endl;
	}
}

/*void Charged::fileInput(string file)
{
	string name, imagename;
	double m, q, x, y, z, vx, vy, vz;
	fstream fin(file.c_str());
	if(!fin)
	{
		cerr<<"Could not open file. Quit and try again"<<endl;
		return;
	}
	while (!fin.eof())//assumes the file is all correct
	{
		fin>>name;
		fin>>imagename;
		fin>>m;
		fin>>q;
		fin>>x;
		fin>>y;
		fin>>z;
		fin>>vx;
		fin>>vy;
		fin>>vz;
		Charged newcharge(name,imagename,m,q,x,y,z,vx,vy,vz);
	}
}*/

void Charged::calcForce()//coulomb force
{
	double k= 8.99e9; //coulomb force constant
	totalForce.clear();

	for (int i=0; i<charges.size(); i++)
	{
		if (&charges[i].get() != this)
		{
			Tensor r = charges[i].get().pos-pos;
			totalForce=totalForce+r*((k*charge*charges[i].get().charge)/(r.getr()*r.getr()*r.getr()));
		}
	}
	accel=totalForce/mass;
}

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
				if (r.getr() <= 20) {
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
	// calculate force for each planet
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().calcForce();

		if (DEBUG) cerr << charges[i].get().name << ":" << endl << charges[i].get().pos << endl << charges[i].get().accel << endl;
	}
	for (int i = 0; i < charges.size(); i++)
	{
		charges[i].get().pos = charges[i].get().pos + charges[i].get().vel*dt + charges[i].get().accel*dt*dt*.5;
		charges[i].get().vel = charges[i].get().vel + charges[i].get().accel*dt;
	}
	collide();


}

#include "Planet.h"

#define DEBUG 1 

// static vector of all planets
vector<Planet> Planet::planets;

//constructor
Planet::Planet(string n, double m, double x, double y, double z) : Body(n, m, x, y, z)
{

	mass = m;
	pos.set(x,y,z);
	planets.push_back(*this);
}

//calculate the force
void Planet::calcForce()//gravitational force
{
	double G=6.67e-11;
	totalForce.clear();

	for (int i = 0; i < planets.size(); i++) 
	{
		// don't add force if it is with itself
		if (&planets[i] != this) 
		{
			Tensor r = planets[i].pos - pos;
			totalForce = totalForce + r*((G*mass*planets[i].mass)/(r.getr()*r.getr()*r.getr()));
		}
	}

	accel = totalForce / mass;
}

void Planet::collide()
{
	if (planets.size()==1){return;}
	int eraseStatus=0;
	cout<<planets.size()<<endl;
	for (int i = 0; i < planets.size(); ++i)
	{
		for (int j = 0; i < planets.size(); ++j)
		{
			if (i==j) {continue;}
			else if((planets[i].pos.getx()-planets[j].pos.getx()<=.1)&&(planets[i].pos.gety()-planets[j].pos.gety()<=.1)&&(planets[i].pos.getz()-planets[j].pos.getz()<=.1))
			{
				cout<<planets[i].name<<planets[j].name<<endl;
				planets.erase (planets.begin()+i);
				cout<<planets.size();
				cout<<planets[j].name<<endl;
				planets.erase (planets.begin()+(j-1));
				eraseStatus=1;
				return;
			}

		}
		if (eraseStatus==1){break;}
	}

}

void Planet::update(double dt)
{
	// calculate force for each planet
	for (int i = 0; i < planets.size(); i++) 
	{
		cout<<planets.size()<<endl;
		planets[i].calcForce();

		if (DEBUG) cout << planets[i].name << ":" << endl << planets[i].pos << endl << planets[i].accel << endl;
	}
	for (int i = 0; i < planets.size(); i++) 
	{
		planets[i].pos = planets[i].pos + (planets[i].vel*dt);
		planets[i].vel = planets[i].vel + (planets[i].accel*dt);
	}
	collide();


}


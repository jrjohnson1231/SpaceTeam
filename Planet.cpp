#include "Planet.h"

#define DEBUG 1

// static vector of all planets
vector<reference_wrapper<Planet> > Planet::planets;

//constructors
Planet::Planet(string name, string imagename, double m, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename) 
{
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	mass = m;
	planets.push_back(*this);
	cout << bodies.size() << endl;
	//cout << "Making " << planets.back().name << endl;
	bodies.push_back(&(planets.back().get()));
}

Planet::Planet(string name, double m, double x, double y, double z, double vx, double vy, double vz) : Body(name) 
{
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	mass = m;
	planets.push_back(*this);
}

//destructor
void Planet::removePtr() 
{
	// find itself in the body vector and removes it
	for (int i = 0; i < bodies.size(); i++) 
	{
		if (bodies[i] == this) 
		{
			bodies.erase(bodies.begin() + i);
		}
	}
	if (DEBUG) 
	{
		cout << "Removing " << name << " pointer"<< endl;
	}
}

void Planet::fileInput(string file)
{
	string name, imagename;
	double m, x, y, z, vx, vy, vz;
	fstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Quit and try again"<<endl;
		return;
	}
	while (!fin.eof())//assumes the file is all correct
	{
		fin>>name;
		fin>>imagename;
		fin>>m;
		fin>>x;
		fin>>y;
		fin>>z;
		fin>>vx;
		fin>>vy;
		fin>>vz;
		Planet newplanet(name,imagename,m,x,y,z,vx,vy,vz);
	}
}

//calculate the force
void Planet::calcForce()//gravitational force
{
	double G=6.67e-11;
	totalForce.clear();

	for (int i = 0; i < planets.size(); i++)
	{
		// don't add force if it is with itself
		if (&planets[i].get() != this)
		{
			Tensor r = planets[i].get().pos - pos;
			totalForce = totalForce + r*((G*mass*planets[i].get().mass)/(r.getr()*r.getr()*r.getr()));
		}
	}

	accel = totalForce / mass;
}

void Planet::collide()
{
	if (planets.size()==1){return;}
	int eraseStatus=0;
	for (int i = 0; i < planets.size(); i++)
	{
		for (int j = 0; j < planets.size(); j++)
		{
			if (i==j) {continue;}
			else {
				Tensor r = planets[i].get().pos - planets[j].get().pos;
				if (r.getr() <= 20) {
					if (DEBUG) cout << planets[i].get().name << " and " << planets[j].get().name << " collided " << endl;
					planets[i].get().removePtr();
					planets[j].get().removePtr();
					planets.erase(planets.begin() + i);
					planets.erase(planets.begin() + j-1);

					eraseStatus=1;
					return;
				}
			}

		}
		if (eraseStatus==1){break;}
	}

}

void Planet::update(double dt)
{
	// calculate force for each planet at initial velocity
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().calcForce();
	}

	// calculate halfway velocity and use it to get position
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().vel = planets[i].get().vel + planets[i].get().accel*dt/2;
		planets[i].get().pos = planets[i].get().pos + planets[i].get().vel*dt;
	}

	// calculate new force
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().calcForce();
		
		// display some debugging info
		if (DEBUG) cout << planets[i].get().name << ":" << endl << planets[i].get().pos << endl << planets[i].get().accel << endl;
	}

	// calculate new velocity based one new force
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].get().vel = planets[i].get().vel + planets[i].get().accel*dt/2;
	}
	collide();


}


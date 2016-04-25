#include "Planet.h"

#define DEBUG 1

// static vector of all planets
vector<Planet> Planet::planets;

//constructors
Planet::Planet(string name, string imagename, double m, double x, double y, double z, double vx, double vy, double vz) : Body(name, imagename) {
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	mass = m;
	planets.push_back(*this);
	bodies.push_back(this);
}

Planet::Planet(string name, double m, double x, double y, double z, double vx, double vy, double vz) : Body(name) {
	pos.set(x, y, z);
	vel.set(vx, vy, vz);
	mass = m;
	planets.push_back(*this);
	bodies.push_back(this);
}

//destructor
Planet::~Planet() {
	// find itself in the body vector and removes it
	for (int i = 0; i < bodies.size(); i++) {
		if (bodies[i] == this) {
			bodies.erase(bodies.begin() + i);
		}
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
	cout << planets.size() << endl;
	for (int i = 0; i < planets.size(); i++)
	{
		for (int j = 0; i < planets.size(); j++)
		{
			if (i==j) {continue;}
			else {
				cout << i << j << endl;
				Tensor r = planets[i].pos - planets[j].pos;
				if (r.getr() <= 20) {
					cout << planets[i].name << " and " << planets[j].name << " collided " << endl;
					cout << planets[i].pos << endl << planets[j].pos << endl;
					cout << i << j << planets.size() << endl;
					planets.erase (planets.begin()+i);
					cout << i << j << planets.size() << endl;
					planets.erase (planets.begin()+(j-1));
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
	// calculate force for each planet
	for (int i = 0; i < planets.size(); i++)
	{
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


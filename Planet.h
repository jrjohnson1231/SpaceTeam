#ifndef PLANET_H
#define PLANET_H

#include "Tensor.h"
#include "Body.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
using namespace std;

//class for planets that act under Newton's Law of Gravitation

class Planet: public Body
{
	public:
		Planet(string name, string imagename, double m=1000, double r=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		Planet(string name, double m=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		void removePtr();
		void calcForce();//calculate the force
		static void collide();
		static void update(double);

	private:
		static vector<reference_wrapper<Planet> > planets; // constains pointer to each object
};

#endif

#ifndef PLANET_H
#define PLANET_H

#include <cmath>
#include "Tensor/Tensor.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "Body.h"
using namespace std;

class Planet: public Body
{
	public:
		Planet(string name, string imagename, double m=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		Planet(string name, double m=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		void removePtr();
		void fileInput(string);
		void calcForce();//calculate the force
		static void collide();
		static void update(double);
		static vector<reference_wrapper<Planet> > planets; // constains pointer to each object

	private:
};

#endif

#ifndef PLANET_H
#define PLANET_H

#include <cmath>
#include "Tensor/Tensor.h"
#include <iostream>
#include <vector>
#include <string>
#include "Body.h"
using namespace std;

class Planet: public Body
{
	public:
		Planet(string name, double m=1000, double x=0, double y=0, double z=0);
		void calcForce();//calculate the force
		static void collide();
		static void update(double);

	private:
		static vector<Planet > planets; // constains pointer to each object
};

#endif

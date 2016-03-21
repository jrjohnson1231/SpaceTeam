#ifndef PLANET_HPP
#define PLANET_HPP
#include <cmath>
#include "Tensor/Tensor.h"
#include <iostream>
using namespace std;

class Planet
{
	public:
		Planet(double m=1000, double x=0, double y=0, double z=0);
		Tensor calcAccel();
		double calcPos();
		double calcVel();
		double getMass();
		double getx();
		double gety();
		double getz();
		Tensor calcForce(Planet);
		double distance(Planet);
		Tensor getPos();
		Tensor getVel();
		void update(double);

	private:
		double mass;
		Tensor accel;
		Tensor totalForce;
		Tensor pos;
		Tensor vel;
};


#endif
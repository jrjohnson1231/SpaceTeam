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
		Tensor calcAccel();//calculate acceleration
		double getMass();
		double getx();
		double gety();
		double getz();
		Tensor calcForce(Planet);//calculate the force
		double distance(Planet);//distance between two planets
		Tensor getPos();
		Tensor getVel();
		void update(double);//move the planets a small amount according to their gravities

	private:
		double mass;
		Tensor accel;
		Tensor totalForce;
		Tensor pos;
		Tensor vel;
};


#endif
#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>
#include "Tensor/Tensor.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Body
{
	public:
		Body(string, double, double, double, double);//constructor
		double getx();
		double gety();
		double getz();
		double getMass();
		virtual void calcForce()=0;
		Tensor getPos();
		Tensor getVel();
		//static void update(double);//move the body a small amount according to it's force

	protected:
		double mass;
		string name;
		Tensor accel;
		Tensor totalForce;
		Tensor pos;
		Tensor vel;
		//static vector<Body *> bodies; // constains pointer to each object
};
//this is an abstract class for different types of bodies (planets or charged particles)


#endif
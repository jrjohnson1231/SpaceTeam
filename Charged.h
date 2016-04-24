#ifndef CHARGEDPARTICLE_H
#define CHARGEDPARTICLE_H

#include <cmath>
#include "Tensor/Tensor.h"
#include "Body.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Charged: public Body
{
	public:
		Charged(string name, string imagename, double m=9.1e-31, double q=1.6e-19, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		Charged(string name, double m=9.1e-31, double q=1.6e-19, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		~Charged();
		void calcForce();//calculate the force
		double getCharge();
		static void collide();
		static void update(double);

	private:
		double charge;
		static vector<Charged> charges; // constains pointer to each object
};

#endif

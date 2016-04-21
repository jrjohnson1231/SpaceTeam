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
		Charged(string name, double m=9.1e-31, double x=0, double y=0, double z=0, double c=1.6e-19);
		void calcForce();//calculate the force
		double getCharge();
		static void update(double);

	private:
		double charge;
		static vector<Charged *> charges; // constains pointer to each object
};

#endif

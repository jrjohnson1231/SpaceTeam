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
		Planet(string name, string imagename, SDL_Surface* screen, double m=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		Planet(string name, double m=1000, double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0);
		~Planet();
		void fileInput(string);
		void calcForce();//calculate the force
		static void collide();
		static void update(double);

	private:
		static vector<Planet > planets; // constains pointer to each object
};

#endif

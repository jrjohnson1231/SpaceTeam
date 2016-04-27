#ifndef BODY_HPP
#define BODY_HPP

#include "Tensor.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#undef main
#include <SDL_image/SDL_image.h>
#include <fstream>
using namespace std;

//this is an abstract class for different types of bodies (planets or charged particles)

class Body
{
	friend class Window;

	public:
		Body(string, double, double, double, double);//constructor
		Body(string name, string imagename); // constructor
		Body(string name);//constructor
		double getMass(); // return mass of body
		virtual void calcForce()=0; // calculate force for each object
		Tensor getPos(); // return position of body
		Tensor getVel(); // return velocity of each body
		bool display(SDL_Surface *); // given parameters of window, display image
		static void xRange(double &, double &);
		static void yRange(double &, double &);
		static void calcCOM(); // calculates center of mass of all bodies
		static void calcScale(SDL_Surface *);
		static vector<Body *> bodies; // contains pointer to each object
	
	protected:
		double mass;
		double rad;//radius
		string name;
		string imagename;
		SDL_Surface *image;//pointer to image
		Tensor accel;//acceleration vector
		Tensor totalForce;//force vector
		Tensor pos;//position vector
		Tensor vel;//velocity vector
		static Tensor COM; // initial center of mass of the system
		static double xscale;
		static double yscale;
};

#endif

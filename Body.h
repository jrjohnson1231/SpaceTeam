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
		bool display(SDL_Surface *, Tensor, Tensor, int, int); // given parameters of window, display image
		int getx(Tensor topleft,Tensor botright, int height, int width);
		int gety(Tensor topleft,Tensor botright, int height, int width);
		static void calcCOM(); // calculates center of mass of all bodies
		static vector<Body *> bodies; // constains pointer to each object
	
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
		static Tensor COM; // center of mass vector
};

#endif

#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>
#include "Tensor/Tensor.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <fstream>
#undef main
#include <SDL_image/SDL_image.h>
using namespace std;


class Body
{
	friend class Window;

	public:
		Body(string, SDL_Surface* inscreen, double, double, double, double);//constructor
		Body(string name, string imagename); // constructor
		Body(string name);
		double getMass(); // return mass of body
		virtual void calcForce()=0; // calculate force for each object
		Tensor getPos(); // return position of body
		Tensor getVel(); // return velocity of each body
		//static void update(double);//move the body a small amount according to it's force
		bool display(Tensor, Tensor, int, int); // given parameters of window, display image
		int getx(Tensor topleft,Tensor botright, int height, int width);
		int gety(Tensor topleft,Tensor botright, int height, int width);
	protected:
		double mass;
		string name;
		string imagename;
		SDL_Surface* screen;	//Pointer to screen, which is outside of object
		SDL_Rect offset;    //Offset of image
		SDL_Surface *image;
		Tensor accel;
		Tensor totalForce;
		Tensor pos;
		Tensor vel;
		static vector<Body *> bodies; // constains pointer to each object
};
//this is an abstract class for different types of bodies (planets or charged particles)

#endif

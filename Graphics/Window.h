#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"
#include "Tensor.h"
#include "../Planet.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Window
{
	public:
		Window(std::string windowname, string infile, int i_height=640, int i_width=480, int i_bpp=32);
		~Window();
		int createobj(std::string imagename, Tensor t);
		int createobj(std::string message, int fontsize,
									std::string fontname, int x, int y);
		bool removeobj(int obj_num);
		bool returnobj(int obj_num);
		void addObject(Object *);
		bool colorobj(int,Uint8,Uint8,Uint8);
		bool move(int obj_number, Tensor t);
		int getheight();
		int getwidth();
		bool display();
		bool reset();
		void update(int dt=1);
		void run();
		void handle_events();
		void updateTime(double);
		void newmessage(int, string);
		void printText(string, string, int, SDL_Color);
		vector<Body *> readFile(string);
		void cleanup(vector<Body *>);
	private:
		SDL_Surface* screen;
		SDL_Surface* background;
		SDL_Event event;
		int height;
		int width;
		int bpp;
		std::vector<Object *> obj;
		vector<Body *> objects;
		Tensor topleft;
		Tensor botright;
		int getx(Tensor,int);
		int gety(Tensor,int);
		bool quit;
		double time; // time in seconds
		int dt = 1800;
		int time_obj;
};

#endif // WINDOW_H

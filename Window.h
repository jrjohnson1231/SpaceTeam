#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>
#include "Tensor.h"
#include "Planet.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Window
{
	public:
		Window(std::string windowname, string infile, int i_height=640, int i_width=480, int dt=1, int i_bpp=32);
		~Window();

		// Updates and displays planets and handles events continuously
		void run();

		// Event handling function
		void handle_events();

		// Display functions
		bool display();
		bool reset();
		void printText(string, string, int, SDL_Color);

		// Update time passed
		void updateTime(double);

		//Read in body information
		vector<Body *> readFile(string);

		// Cleanup body information
		void cleanup(vector<Body *>);
	private:
		SDL_Surface* screen;
		SDL_Surface* background;
		SDL_Event event;
		int height;
		int width;
		int bpp;
		vector<Body *> objects;
		bool quit;
		bool pause;
		double time; // time in seconds
		int dt;
};

#endif // WINDOW_H

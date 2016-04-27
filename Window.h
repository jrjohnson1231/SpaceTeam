#ifndef WINDOW_H
#define WINDOW_H

#ifndef DEBUG
#define DEBUG 0
#endif

#include "Tensor.h" // math vector class
#include "Planet.h" // planetary body class
#include "Charged.h" // charged body class
#include <string> // string
#include <sstream> // string streams
#include <vector> // vector
#include <iostream> // cerr, cout
#include <iomanip> // setw
#include <cstdlib> // exit
#include <SDL/SDL.h> // graphics libraries
#include <SDL_image/SDL_image.h> // graphics image libraries
#include <SDL_ttf/SDL_ttf.h> // graphics text libraries
using namespace std;

/* This class provides a base for making an SDL Window to display our simulation
 * It includes functions to read the file, create/destroy objects, and run the actual simulation */

class Window
{
	public:
		// Constructors
		Window(std::string windowname, string infile, int i_height=640, int i_width=480, int dt=1, int i_bpp=32);

		// Destructors
		~Window();

		// Member Functions
		void run(); // Updates and displays planets and handles events continuously
		void handle_events(); // Handles all SDL events
		bool display(); // Displays everything on screen
		bool reset(); // Resets screen between displays
		void printText(string, string, int, SDL_Color); // Prints text to screen
		void updateTime(unsigned long long int); // Updates the time the simulation has been running
		vector<Body *> readFile(string); // Read bodies from file
		void cleanup(vector<Body *>); // Cleanup bodies

	private:
		// SDL variables
		SDL_Surface* screen; // Main screen
		SDL_Surface* background; // Background image
		SDL_Event event;

		// Window variables
		int height; // Height of screen
		int width; // Width of screen
		int bpp;

		// Body vector
		vector<Body *> objects; // Vector of all objects on screen

		// Simulation variables
		bool quit;
		bool pause;
		unsigned long long int time; // Time in seconds
		unsigned long long int dt; // Timestep in seconds
};

#endif // WINDOW_H

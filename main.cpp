#include "Window.h"
#include "Tensor.h"
#include "Planet.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define DEBUG 0

void usage(string, int);

int main ( int argc, char** argv )
{
	string filename;
	unsigned long long dt;

	if (argc==3)
    {
		try
		{
			filename = argv[1];
			long long temp = atoll(argv[2]);
			dt = (unsigned long long)temp;
		}
		catch (...)
		{
			cerr << "Couldn't read command line arguments!" << endl;
			usage(argv[0], -1);
		}
	}
    else if (argc==2)
    {
    	try
		{
			filename = argv[1];
			dt = 1;
		}
		catch(...)
		{
			cerr << "Couldn't read command line arguments!" << endl;
			usage(argv[0], -1);
		}
	}
	else if (argc == 1)
	{
		filename = "planets.txt";
		dt = 1;
	}
    else 
    {
    	cerr << "That is not a valid command line argument!" << endl;
		usage(argv[0], -1);
    }

	// Make window and execute simulation
	Window w(filename, filename, 800, 600, dt);
	w.run();
	
	return 0;
}

void usage(string program_name, int exit_status)
{
	cerr << "Usage: " << program_name << " [filename] [dt]" << endl << endl;
	exit(exit_status);
}

#include "Window.h"


/* ----- CONSTRUCTORS ----- */
Window::Window(std::string windowname,string inputfile, int i_height,int i_width,int dt, int i_bpp)
			: height(i_height),width(i_width),bpp(i_bpp),dt(dt)
{
	//Start SDL, TTF
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cerr << "SDL_Init() failed: " << SDL_GetError() << endl;
		exit(1);
	}
	if (TTF_Init() != 0)
	{
		cerr << "TTF_Init() failed: " << TTF_GetError() << endl;
		exit(1);
	}

	// Load support for the JPG and PNG image formats
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if((initted&flags) != flags) // Check for failure
	{
		cerr<<"IMG_Init: Failed to init required jpg and png support " << IMG_GetError() << endl;
		exit(1);
	}

	// Create screen
	screen = SDL_SetVideoMode(height,width,bpp,SDL_SWSURFACE | SDL_RESIZABLE);
	SDL_WM_SetCaption(windowname.c_str(), NULL);

	// Set simulation variables
	quit = 0;
	pause = 0;

	// Load background image
	SDL_Surface* loadedimage = IMG_Load("images/Space.jpg");
	if (loadedimage == NULL) // Check for failure
	{
		cerr << "ERROR: background image load failed" << SDL_GetError() << endl;
		exit(1);
		return;
	}

	// Reformat background image
	background = SDL_DisplayFormat(loadedimage);
	if (background == NULL) // Check for failure
	{
		cerr << "ERROR: background image conversion failed" << SDL_GetError() << endl;
		exit(1);
		return;
	}

	// Free temporary image
	SDL_FreeSurface(loadedimage);


	// Inititalize time
	time = 0;

	// Read input file
	objects = readFile(inputfile);

	// Calculate scale for bodies
	Body::calcScale(screen);
}


/* ----- DESTRUCTORS ----- */
Window::~Window()
{
	//Cleanup and quit SDL
	cleanup(objects);
	TTF_Quit();
	SDL_Quit();
}


/* ----- MEMBER FUNCTIONS ----- */

/* Updates and displays planets and handles events continuously */
void Window::run()
{
	// Continue until program closes
	while(!quit)
	{
		// Get events
		while(SDL_PollEvent(&event))
		{
			handle_events();
		}
		// Run simulation
		if(!pause)
		{
			Planet::update(dt);
			reset();
			display();
			updateTime(dt);

			// Push planets to screen
			SDL_Flip(screen);
		}
	}
}

/* Event handling function */
void Window::handle_events()
{
	// User closes window
	if (event.type == SDL_QUIT){
		quit = true;
		return;
	}
}

/* Display function */
bool Window::display()
{
	// Loop over all bodies and display them
	for (int i = 0; i < Body::bodies.size(); i++)
	{
		Body::bodies[i]->display(screen);
	}

	return 0;
}

/* Return screen to background image */
bool Window::reset()
{
	SDL_BlitSurface(background,NULL,screen, NULL);
	return 0;
}

/* Display message */
void Window::printText(string message, string fontname, int fontsize, SDL_Color color)
{
	// Debugging message
	if (DEBUG) cerr << "Displaying " << message << endl;

	// Render font
	TTF_Font *font = TTF_OpenFont(fontname.c_str(), fontsize);
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() failed: " << TTF_GetError() << endl;
		exit(1);
		return;
	}

	// Render text
	SDL_Surface *text = TTF_RenderText_Solid(font, message.c_str(), color);
	if (text == NULL)
	{
		cerr << "TTF_RenderText_Solid() failed: " << TTF_GetError() << endl;
		exit(1);
		return;
	}

	// Display to screen
	if (SDL_BlitSurface(text, NULL, screen, NULL) != 0)
	{
		cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
		exit(1);
		return;
	}

	// Close font
	TTF_CloseFont(font);
}

/* Update time passed */
void Window::updateTime(unsigned long long int dt)
{
	// Increment time
	time += dt;

	// Convert to Years, Months, Days, Hours, Minutes, Seconds
	int years = time / 60 / 60 / 24 / 30 / 12;
	int months = (time / 60 / 60 / 24 / 30) % 12;
	int days = (time / 60 / 60 / 24) % 30;
	int hours = (time / 60 / 60) % 24;
	int mins = (time / 60) % 60;
	int secs = time % 60;

	// Make string
	ostringstream timeconvert;
	timeconvert << years << " Years, " << months << " Months, " << days << " Days, " << setw(2) << hours << " Hours, " << setw(2) << mins << " Minutes, " << setw(2) << secs << " Seconds";
	string timestring = timeconvert.str();

	// Print to screen
	printText(timestring, "fonts/arial.ttf", 14, {255, 255, 255});
}

/* Read in body information */
vector<Body *> Window::readFile(string file)
{
	// Make an empty vector
	vector<Body *> objects;

	// Declare variables
	string name, imagename;
	string m, r, x, y, z, vx, vy, vz;

	// Make file stream
	ifstream fin(file.c_str());
	if(!fin) // Error opening file
	{
		cerr <<"Could not open file. Try again"<<endl;
		return objects;
	}

	// Read file
	while (!fin.eof()) // Assumes the file is all correct
	{
		getline(fin,name,',');
		//fin>>name;
		//fin>>imagename;
		getline(fin, imagename,',');
		getline(fin,m,',');
		getline(fin,r,',');
		getline(fin,x,',');
		getline(fin,y,',');
		getline(fin,z,',');
		getline(fin,vx,',');
		getline(fin,vy,',');
		getline(fin,vz,',');

		// Make new body
		Body *newP;

		// Debugging message
		if (DEBUG) cerr << "Getting " << name << " from file..." << endl;

		// Construct planet
		newP = new Planet(name,imagename,atof(m.c_str()),atof(r.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));

		// Push back to vector
		if (newP != NULL)
		{
			objects.push_back(newP);
		}
		else // catch errors
		{
			cerr << "Could not initialize " << name << endl;
			exit(1);
		}

		// Read \n that follows line
		getline(fin, m); // m is dummy variable
	}
	return objects;
}

/* Cleanup body information */
void Window::cleanup(vector<Body *> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		// Take off vector and delete it
		Body *ptr = objects.back();
		objects.pop_back();
		delete ptr;
	}
}

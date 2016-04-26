#include "Window.h"


Window::Window(std::string windowname,string inputfile, int i_height,int i_width,int i_bpp)
			: height(i_height),width(i_width),bpp(i_bpp)
{
	//Start SDL, TTF
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init() failed: " << SDL_GetError() << endl;
	}
	if (TTF_Init() != 0)
	{
		cout << "TTF_Init() failed: " << TTF_GetError() << endl;
	}

	// load support for the JPG and PNG image formats
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if((initted&flags) != flags)
	{
		cout<<"IMG_Init: Failed to init required jpg and png support " << IMG_GetError() << endl;
	}

	//Create screen
	screen = SDL_SetVideoMode(height,width,bpp,SDL_SWSURFACE | SDL_RESIZABLE);
	SDL_WM_SetCaption(windowname.c_str(), NULL);
	quit = 0;

	//Load background image
	SDL_Surface* loadedimage = IMG_Load("images/Space.jpg");
	if (loadedimage == NULL)
	{
		cout << "ERROR: background image load failed" << SDL_GetError() << endl;
		return;
	}
	background = SDL_DisplayFormat(loadedimage);
	if (background == NULL)
	{
		cout << "ERROR: background image conversion failed" << SDL_GetError() << endl;
		return;
	}
	SDL_FreeSurface(loadedimage);


	// Inititalize time
	time = 0;

	// Read input file
	objects = readFile(inputfile);
}

Window::~Window()
{
	//Cleanup and quit SDL
	cleanup(objects);
	TTF_Quit();
	SDL_Quit();
}

// Updates and displays planets and handles events continuously
void Window::run()
{
	// Continue until program closes
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			handle_events();
		}
		if(!pause)
		{
			Planet::update(dt);
			reset();
			display();
			updateTime(dt);
		}
	}
}

// Event handling function
void Window::handle_events()
{
	// User closes window
	if (event.type == SDL_QUIT){
		quit = true;
		return;
	}
	if (event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_p : pause = !pause;
		}
	}
}

// Display functions
bool Window::display()
{
	//reset();
	for (int i = 0; i < Body::bodies.size(); i++)
	{
		Body::bodies[i]->display(screen);
	}

	SDL_Flip(screen);
	return 0;
}

// Return screen to background image
bool Window::reset()
{
	SDL_BlitSurface(background,NULL,screen, NULL);
	return 0;
}

// Display message
void Window::printText(string message, string fontname, int fontsize, SDL_Color color)
{
	cout << "Displaying " << message << endl;
	// Render font and text
	TTF_Font *font = TTF_OpenFont(fontname.c_str(), fontsize);
	if (font == NULL)
	{
		cout << "TTF_OpenFont() failed: " << TTF_GetError() << endl;
		return;
	}

	SDL_Surface *text = TTF_RenderText_Solid(font, message.c_str(), color);
	if (text == NULL)
	{
		cout << "TTF_RenderText_Solid() failed: " << TTF_GetError() << endl;
		return;
	}

	// Display to screen
	if (SDL_BlitSurface(text, NULL, screen, NULL) != 0)
	{
		cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
		return;
	}
	SDL_Flip(screen);
	TTF_CloseFont(font);
}

// Update time passed
void Window::updateTime(double dt)
{
	// Increment time
	time += dt;
	int total_seconds = int(time);

	// Convert to Years, Months, Days, Hours, Minutes, Seconds
	int years = total_seconds / 60 / 60 / 24 / 30 / 12;
	int months = (total_seconds / 60 / 60 / 24 / 30) % 12;
	int days = (total_seconds / 60 / 60 / 24) % 30;
	int hours = (total_seconds / 60 / 60) % 24;
	int mins = (total_seconds / 60) % 60;
	int secs = total_seconds % 60;

	ostringstream timeconvert;
	timeconvert << years << " Years, " << months << " Months, " << days << " Days, " << setw(2) << hours << " Hours, " << setw(2) << mins << " Minutes, " << setw(2) << secs << " Seconds";
	string timestring = timeconvert.str();
	printText(timestring, "fonts/arial.ttf", 14, {255, 255, 255});
}

//Read in body information
vector<Body *> Window::readFile(string file)
{
	vector<Body *> objects;
	string name, imagename;
	string m, r, x, y, z, vx, vy, vz;
	ifstream fin(file.c_str());
	if(!fin)
	{
		cout<<"Could not open file. Try again"<<endl;
		return objects;
	}
	while (!fin.eof())//assumes the file is all correct
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
		Body *newP = new Planet(name,imagename,atof(m.c_str()),atof(r.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));
		if (newP != NULL)
		{
			objects.push_back(newP);
		}
		else
		{
			cout << "Could not initialize " << name << endl;
		}
		// Flush trailing \n
		string dummy;
		getline(fin, dummy);
	}
	return objects;
}

// Cleanup body information
void Window::cleanup(vector<Body *> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects.erase(objects.begin());
	}
}

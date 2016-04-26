#include "Window.h"
#include <sstream>

Window::Window(std::string windowname,string inputfile, int i_height,int i_width,int i_bpp)
			: height(i_height),width(i_width),bpp(i_bpp){
	//Start SDL
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
	if((initted&flags) != flags) {
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
	Tensor t(0,0);
	topleft = t;
	botright= t;

	// Inititalize time
	time = 0;


	// Read input file
	objects = readFile(inputfile);
	// Create time object for display
	//time_obj = createobj("Time",12,"fonts/arial.ttf",0,0);
}

Window::~Window(){
	for(unsigned int i=0;i<obj.size();i++){
		obj[i]->free();
	}
	cleanup(objects);
	TTF_Quit();
	SDL_Quit();
}

// TODO (Chris#1#): Fix to Tensor
int Window::createobj(std::string imagename, Tensor t){
	Object newobj(imagename,screen,0,0);
	obj.push_back(&newobj);
	move(obj.size()-1,t);
	return obj.size()-1;
}

int Window::createobj(std::string message, int fontsize,
											std::string fontname, int x, int y){
	Object newobj(message,fontsize,fontname,screen,x,y);
	obj.push_back(&newobj);
	return obj.size()-1;
}

void Window::newmessage(int obj_num,std::string message){
	obj[obj_num]->newmessage(message);
}

void Window::addObject(Object * o) {
	obj.push_back(o);
}

bool Window::removeobj(int obj_num){
	obj[obj_num]->invisible();
	return 0;
}

bool Window::returnobj(int obj_num){
	obj[obj_num]->revisible();
	return 0;
}

bool Window::colorobj(int obj_num,Uint8 r,Uint8 g,Uint8 b){
	obj[obj_num]->setFontColor(r,g,b);
	return 0;
}

bool Window::move(int obj_number, Tensor t){
	int x = getx(t,obj_number);
	int y = gety(t,obj_number);
	obj[obj_number]->move(x,y);
	return 0;
}

int Window::getheight(){
	return height;
}

int Window::getwidth(){
	return width;
}

bool Window::display(){

	//reset();
	for (int i = 0; i < Body::bodies.size(); i++) {
		Body::bodies[i]->display(screen, topleft, botright, 10, 10);
	}
	/*for(unsigned int i = 0;i<obj.size();i++){
		//obj[i]->update();
		if (obj[i]->isVisible()) {
			SDL_BlitSurface(obj[i]->getImage(), NULL, screen, NULL);
		}
	}*/
	//Earth.display(screen, topleft,botright,height,width);
	//Moon.display(screen, topleft,botright,height,width);
	SDL_Flip(screen);
	return 0;
}

bool Window::reset(){
	SDL_BlitSurface(background,NULL,screen, NULL);
	return 0;
}

void Window::update(int dt){
	//Earth.update(dt);
}

void Window::run(){
	while(!quit){
		while(SDL_PollEvent(&event)){
			handle_events();
		}
		Planet::update(dt);
		reset();
		display();
		updateTime(dt);
	}
}

void Window::handle_events(){
	// User closes window
	if (event.type == SDL_QUIT){
		quit = true;
		return;
	}
}

int Window::getx(Tensor t,int obj_number){
	double numer = t.getx() - topleft.getx();
	double denom = botright.getx() - topleft.getx();
	return (numer/denom * height) - obj[obj_number]->geth();
}
int Window::gety(Tensor t, int obj_number){
	double numer = t.gety() - topleft.gety();
	double denom = botright.gety() - topleft.gety();
	return numer/denom * width - obj[obj_number]->getw();
}

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
	//newmessage(time_obj,timestring);
}

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
	//SDL_FreeSurface(text);
}

vector<Body *> Window::readFile(string file)
{
	vector<Body *> objects;
	string name, imagename;
	string m, x, y, z, vx, vy, vz;
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
	getline(fin,x,',');
		getline(fin,y,',');
		getline(fin,z,',');
		getline(fin,vx,',');
		getline(fin,vy,',');
		getline(fin,vz,',');
		Body *newP = new Planet(name,imagename,atof(m.c_str()),atof(x.c_str()),atof(y.c_str()),atof(z.c_str()),atof(vx.c_str()),atof(vy.c_str()),atof(vz.c_str()));
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

void Window::cleanup(vector<Body *> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects.erase(objects.begin());
	}
}

#include "Window.h"
#include <sstream>

Window::Window(std::string windowname, Tensor tl, Tensor br,int i_height,int i_width,int i_bpp)
			: height(i_height),width(i_width),bpp(i_bpp){
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Create screen
	screen = SDL_SetVideoMode(height,width,bpp,SDL_SWSURFACE | SDL_RESIZABLE);
	SDL_WM_SetCaption(windowname.c_str(), NULL);
	topleft = tl;
	botright = br;
	quit = 0;
	//Load background image
	SDL_Surface* loadedimage = IMG_Load("images/Space.jpg");
	if (loadedimage == NULL)
	{
		cout << "ERROR: background image load failed" << SDL_GetError() << endl;
		return;
	}
	background = SDL_DisplayFormat(loadedimage);
	SDL_FreeSurface(loadedimage);
	//Planet Earth("Earth","images/red_square.jpg", 5);
	//Planet Moon("Moon","images/black_square.jpg", 4, 4,3);

	// Inititalize time
	time = 0;
}

Window::~Window(){
	for(unsigned int i=0;i<obj.size();i++){
		obj[i]->free();
	}
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

	reset();
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
	while (!quit){
		while(SDL_PollEvent(&event)){
			handle_event(event);
		}
		update();
		display();

	}
}

void Window::handle_event(SDL_Event event){
	if(event.type == SDL_QUIT){
		quit = true;
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
	timeconvert << years << " Years, " << months << " Months, " << days << " Days, " << hours << " Hours, " << mins << " Mins, " << secs << " Secs";
	timestring = timeconvert.str();
	cout << timestring << endl;
}

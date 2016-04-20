#include "Window.h"

Window::Window(std::string windowname, Tensor tl, Tensor br,int i_height,int i_width,int i_bpp)
			: height(i_height),width(i_width),bpp(i_bpp){
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Create screen
	screen = SDL_SetVideoMode(height,width,bpp,SDL_SWSURFACE | SDL_RESIZABLE);
	reset();
	SDL_WM_SetCaption(windowname.c_str(), NULL);
	topleft = tl;
	botright = br;
	quit = 0;
}

Window::~Window(){
	for(unsigned int i=0;i<obj.size();i++){
		obj[i].free();
	}
	TTF_Quit();
	SDL_Quit();
}

// TODO (Chris#1#): Fix to Tensor
int Window::createobj(std::string imagename, Tensor t){
	Object newobj(imagename,screen,0,0);
	obj.push_back(newobj);
	move(obj.size()-1,t);
	return obj.size()-1;
}

int Window::createobj(std::string message, int fontsize,
											std::string fontname, int x, int y){
	Object newobj(message,fontsize,fontname,screen,x,y);
	obj.push_back(newobj);
	return obj.size()-1;
	}

bool Window::removeobj(int obj_num){
	obj[obj_num].invisible();
	return 0;
}

bool Window::returnobj(int obj_num){
	obj[obj_num].revisible();
	return 0;
}

bool Window::colorobj(int obj_num,Uint8 r,Uint8 g,Uint8 b){
	obj[obj_num].setFontColor(r,g,b);
	return 0;
}

bool Window::move(int obj_number, Tensor t){
	int x = getx(t,obj_number);
	int y = gety(t,obj_number);
	obj[obj_number].move(x,y);
	return 0;
}

int Window::getheight(){
	return height;
}

int Window::getwidth(){
	return width;
}

bool Window::update(){

	reset();
	for(unsigned int i = 0;i<obj.size();i++){
		obj[i].update();
	}
	SDL_Flip(screen);
	return 0;
}

bool Window::reset(){
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xE0, 0xE0, 0xE0 ) );
	return 0;
}

// Helper functions

int Window::getx(Tensor t,int obj_number){
	double numer = t.getx() - topleft.getx();
	double denom = botright.getx() - topleft.getx();
	return (numer/denom * height) - obj[obj_number].geth();
}
int Window::gety(Tensor t, int obj_number){
	double numer = t.gety() - topleft.gety();
	double denom = botright.gety() - topleft.gety();
	return numer/denom * width - obj[obj_number].getw();
}
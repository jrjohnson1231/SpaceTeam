#ifndef OBJECT_H
#define OBJECT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "../Planet.h"
#include <string>
#include <iostream>
using namespace std;

class Object{
	public:
		Object(std::string imagename, SDL_Surface* screen, int x, int y);
		Object(string imagename, Planet *);
		Object(std::string message, int fontsize, std::string fontname,
																	SDL_Surface* screen, int x, int y);
		bool newmessage(std::string message);
		bool setFontColor(Uint8 r, Uint8 g, Uint8 b);
		bool move(int x, int y);	//Move the object
		bool update();						//Update the object
		bool free();							//Free the object
		bool isVisible();
		SDL_Surface *getImage();
		SDL_Rect *getOffset();
		void invisible();
		void revisible();
		int geth();
		int getw();
	private:
		SDL_Surface* screen;	//Pointer to screen, which is outside of object
		SDL_Surface* image;		//Pointer to image
		TTF_Font* font;				//Font pointer
		SDL_Color color;			//Currently only black
		SDL_Rect offset;			//Rectangle that defines position of object
		std::string message;
		bool visible;
		Planet *planet; // Pointer to planet
};

#endif // OBJECT_H

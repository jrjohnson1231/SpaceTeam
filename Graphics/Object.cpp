#include "Object.h"

Object::Object(std::string imagename, SDL_Surface* inputscreen, int x, int y){
	//Set screen variable
	screen = inputscreen;

	//Load Image
	SDL_Surface* loadedimage = NULL;
	loadedimage = IMG_Load(imagename.c_str());

	//Set Optimized image
	image = SDL_DisplayFormat(loadedimage);

	//Free load image
	SDL_FreeSurface(loadedimage);

	//Set offset
	offset.x = x;
	offset.y = y;

	//Set unused pointer to NULL
	font = NULL;

	//Set visibility
	visible = 1;

}

Object::Object(std::string in_message, int fontsize, std::string fontname, SDL_Surface* inputscreen, int x, int y){
	//Set screen pointer
	screen = inputscreen;

	//Load Font
	font = TTF_OpenFont(fontname.c_str(),fontsize);

	color.r = 0;
	color.g = 0;
	color.b = 0;

	//Load message image
	message = in_message;
	image = TTF_RenderText_Solid(font,message.c_str(), color);

	//Set offset
	offset.x = x;
	offset.y = y;

	//Set visibility
	visible = 1;
}


bool Object::newmessage(std::string message){
	if(font){
		image = TTF_RenderText_Solid(font,message.c_str(),color);
		return 0;
	}
	else return 1;
}

bool Object::setFontColor(Uint8 r, Uint8 g, Uint8 b){
	color.r = r;
	color.g = g;
	color.b = b;
	image = TTF_RenderText_Solid(font,message.c_str(), color);
	return 0;
}

bool Object::move(int x, int y){
	//Reset offset
	offset.x = x;
	offset.y = y;
	return 0;
}

bool Object::update(){
	//Blit Image
	if(visible) SDL_BlitSurface(image, NULL, screen, &offset);
  return 0;
}


bool Object::free(){
	//Free image
	SDL_FreeSurface(image);
	if(font){
		TTF_CloseFont(font);
	}
	return 0;
}

void Object::invisible(){
	visible = 0;
}

void Object::revisible(){
	visible = 1;
}

int Object::geth(){
	return image->h;
}

int Object::getw(){
	return image->w;
}

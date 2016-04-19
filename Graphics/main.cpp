#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Window.h"
#include "Timer.h"
#include "Tensor.h"
#include <iostream>
#include <string>

int main ( int argc, char** argv ){
    Tensor t(-1e24,-1e24);
    Tensor t2(1e24,1e24);
    Tensor t3(0,0);
    Tensor t4(1e22,1e22);
    Window w("Test",t,t2,800,300);
    int red = w.createobj("images/red_square.jpg",t+t4);
    for(int i = 1; i < 200; i++){
			w.update();
			SDL_Delay(20);
			w.move(red,t+(t4*i));
    }
    w.createobj("images/black_square.jpg",t3);
    w.update();
    SDL_Delay(2000);
    return 0;
}

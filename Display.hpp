#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "nPuzzle.hpp"
#include "Board.hpp"
#include <SDL2/SDL.h>

class Display {
private:
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Texture* pic[4];
	SDL_Event event;
public:
	bool step;
	bool nxstep;
	char c;
    Display();
    ~Display();
    void refresh(PTR, PTR, bool);
    void SDL_Start();
    void get_input();
};

#endif

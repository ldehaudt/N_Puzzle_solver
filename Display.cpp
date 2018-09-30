#include "Display.hpp"

void	Display::refresh(PTR b, PTR end, bool finish)
{
	get_input();
	while (step && !nxstep)
		get_input();
	nxstep = 0;
	int sidelen = 1200 / b->size;
	SDL_RenderClear(rend);
	SDL_Rect rect = {0, 0, sidelen, sidelen};
	SDL_Rect rectWin = {0, 0, sidelen, sidelen};
	for (int i = 0; i < b->size * b->size; i++)
	{
		rectWin.x = sidelen * (i % b->size);
		rectWin.y = sidelen * (i / b->size);
		rect.x = sidelen * (static_cast<int>(end->findNumber(b->str[i])) % b->size);
		rect.y = sidelen * (static_cast<int>(end->findNumber(b->str[i])) / b->size);

		SDL_RenderCopy(rend, pic[c], &rect, &rectWin);
	}
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	if (!finish){
		rect.x = sidelen * (b->zero % b->size);
		rect.y = sidelen * (b->zero / b->size);
		SDL_RenderFillRect(rend, &rect);
	}
	SDL_RenderPresent(rend);
	while (finish)
		get_input();
}

void	Display::SDL_Start()
{
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("nPuzzle", 1200, 0, 1200, 1200, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(win, -1, 0);
	SDL_Surface *tmpSurf;
	tmpSurf = SDL_LoadBMP("pic.bmp");
	pic[0] = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("galaxy.bmp");
	pic[1] = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("EGG.bmp");
	pic[2] = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("GAETAN.bmp");
	pic[3] = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
}

void	Display::get_input()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			exit (1);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				step = !step;
				nxstep = 0;
			}
			if (step && event.key.keysym.sym == SDLK_RIGHT)
				nxstep = 1;
			if (event.key.keysym.sym == SDLK_4
				|| event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_2
				|| event.key.keysym.sym == SDLK_3)
				c = event.key.keysym.sym - SDLK_1;
		}
	}
}

Display::Display(){
	SDL_Start();
	step = 0;
	nxstep = 0;
	c = 0;
}

Display::~Display(){
	for (int i = 0; i < 4; i++)
		SDL_DestroyTexture(pic[i]);
}

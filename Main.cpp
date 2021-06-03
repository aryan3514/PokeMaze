

#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Unit.h"
#include "Pokeball.h"
#include "Squirtle.h"
#include "Wall.h"
#include "Gastly.h"
#include "Monster.h"
#include "JigglyPuff.h"
#include "Matrix.h"
#include "Zoroark.h"
#include "Ash.h"
#include <iostream>
#include <stdio.h>


using namespace std;

const int WIDTH = 960;
const int HEIGHT = 540;

SDL_Window* Game_Window = NULL;
SDL_Renderer* Game_Renderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* Game_s = NULL;

Matrix Game_Matrix(25, 25);

int main(int argc, char* argv[]) {
	Game_Window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (Game_Window == NULL) {
		cout << "HEY< ERROR" << endl;
	}

	Game_Renderer = SDL_CreateRenderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Game_Renderer == NULL) {
		cout << "HEY< ERROR" << endl;
	}

	gScreenSurface = SDL_GetWindowSurface(Game_Window);
	Game_s = SDL_LoadBMP("n.bmp");
	SDL_BlitSurface(Game_s, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(Game_Window);
	//Texture::Renderer = Game_Renderer;
	SDL_Delay(5000);
	return 0;
}
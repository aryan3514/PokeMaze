

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
#include "Summon.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;

const int WIDTH = 720;
const int HEIGHT = 720;

SDL_Window* Game_Window = NULL;
SDL_Renderer* Game_Renderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* Game_s = NULL;
SDL_Texture* Tex = NULL;

Matrix Game_Matrix(38, 38);

Summon Summoner(&Game_Matrix);

vector <Element*> AllFinElements;

int main(int argc, char* argv[]) {

	ofstream MyFile("debhug.txt");
	Game_Window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (Game_Window == NULL) {
		cout << "HEY< ERROR" << endl;
	}

	Game_Renderer = SDL_CreateRenderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Game_Renderer == NULL) {
		cout << "HEY< ERROR" << endl;
	}
	Texture::Renderer = Game_Renderer;
	
	map<string, Texture*> TextureHash;
	

	Texture* pokeball_texture = new Texture();
	pokeball_texture->LoadImage("c.bmp");
	Element::Element_Matrix = &Game_Matrix;
	TextureHash.insert(pair<string, Texture*>("pokeball", pokeball_texture));
	Summoner.SummonFromMap("map.txt", TextureHash);
	Summoner.SummonAll(AllFinElements);
	
	for (int i = 0; i < AllFinElements.size(); i++) {
		AllFinElements[i]->Refresh();
		AllFinElements[i]->Render();
	}
	

	//Update the surface
	SDL_RenderPresent(Game_Renderer);
	SDL_Delay(10000);
	return 0;
}
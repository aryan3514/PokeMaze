
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
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
#include "Element.h"
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;

const int WIDTH = 1200;
const int HEIGHT = 800;

SDL_Window* Game_Window = NULL;
SDL_Renderer* Game_Renderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* Game_s = NULL;
SDL_Texture* Tex = NULL;

Matrix Game_Matrix(30, 30);

Summon Summoner(&Game_Matrix);

vector <Element*> AllFinElements;




SDL_Color game_textcolor = { 255,255, 255 };

int main(int argc, char* argv[]) {

	TTF_Init();

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	




	TTF_Font* game_font = TTF_OpenFont("C:/Users/91887/Desktop/COP Final/renbow.ttf", 35);

	if (game_font == NULL) {
		return 0;
	}
	
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
	
	Texture* wall_texture = new Texture();
	wall_texture->LoadImage("wall.bmp");

	Texture* ash_texture = new Texture();
	ash_texture->LoadImage("ash.bmp");

	Texture* gastly_texture = new Texture();
	gastly_texture->LoadImage("gastly.bmp");

	Texture* pokeball_texture = new Texture();
	pokeball_texture->LoadImage("pokeball.bmp");

	Texture* zoroark_texture = new Texture();
	zoroark_texture->LoadImage("zoroark.bmp");
	 
	Texture* squirtle_texture = new Texture();
	squirtle_texture->LoadImage("squirtle.bmp");

	Texture* jigglypuff_texture = new Texture();
	jigglypuff_texture->LoadImage("jigglypuff.bmp");

	Texture* monster_texture = new Texture();
	monster_texture->LoadImage("monster.bmp");

	Texture* score_texture = new Texture();
	//score_texture->LoadImage("n.bmp");
	

	//SDL_Rect RenderVals = { 0,0, 30, 760 };
	SDL_Rect ScoreVals = { 0,0, 300, 30};
	

	

	

	Element::Element_Matrix = &Game_Matrix;
	TextureHash.insert(pair<string, Texture*>("wall", wall_texture));
	TextureHash.insert(pair<string, Texture*>("ash", ash_texture));
	TextureHash.insert(pair<string, Texture*>("gastly", gastly_texture));
	TextureHash.insert(pair<string, Texture*>("pokeball", pokeball_texture));
	TextureHash.insert(pair<string, Texture*>("zoroark", zoroark_texture));
	TextureHash.insert(pair<string, Texture*>("squirtle", squirtle_texture));
	TextureHash.insert(pair<string, Texture*>("jigglypuff", jigglypuff_texture));
	TextureHash.insert(pair<string, Texture*>("monster", monster_texture));
	Summoner.SummonFromMap("map.txt", TextureHash);
	Summoner.SummonAll(AllFinElements);

	SDL_Event game_event;
	
	bool run = true; 
	int run2 = true;

	
	

	

	while (run2) {

				
		for (int i = 0; i < AllFinElements.size(); i++) {

			if (AllFinElements.at(i)->toRemove) {
				vector<Element*>::iterator it = AllFinElements.begin();
				while (it != AllFinElements.end()) {
					if (*it == AllFinElements.at(i)) {
						AllFinElements.erase(it);
						break;
					}
					it++;
				}
			}
		}
		


		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.type == SDL_QUIT) {
				run2 = false;
			}

			for (int i = 0; i < AllFinElements.size(); i++) {
				AllFinElements[i]->HandleKeys(&game_event);
			}
		}

		for (int i = 0; i < AllFinElements.size(); i++) {
			AllFinElements[i]->Refresh();
			//AllFinElements[i]->Render();
		}

		
		SDL_RenderClear(Game_Renderer);

		

		for (int i = 0; i < AllFinElements.size(); i++) {
			//AllFinElements[i]->Refresh();
			AllFinElements[i]->Render();
		}

		score_texture->LoadText(game_font, game_textcolor, "Ankita's score : " + to_string(Ash::points));
		score_texture->Render(50+200, 15, &ScoreVals, 0.0, NULL, SDL_FLIP_NONE);
		score_texture->LoadText(game_font, game_textcolor, "Aryan's score : 0" );
		score_texture->Render(420+200, 15, &ScoreVals, 0.0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(Game_Renderer);
		

	}

	
	//Update the surface
	
	//SDL_Delay(10000);
	return 0;
}
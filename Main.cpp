
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
#include <ctime>

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

void AbilityAction(Matrix* Game_Matrix, time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer,bool &s, bool &j, bool &g, bool &z) {

	if (Game_Matrix->FindAsh()->squrtle) {
		
		Game_Matrix->FindAsh()->squrtle = false;
		for (int i = 0; i < AllFinElements.size(); i++) {
			if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
				AllFinElements[i]->GetMonsterFromElements()->Remove();
				break;
			}
		}
		s = true;
		time(&squirtle_timer);
	}
	
	if (Game_Matrix->FindAsh()->gastly) {
		for (int i = 0; i < AllFinElements.size(); i++) {
			if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
				AllFinElements[i]->GetMonsterFromElements()->ConfuseMonster();
				Game_Matrix->FindAsh()->gastly = false;
				//break;
			}
		}
		g = true;
		time(&gastly_timer) ;
	}
	 
	if (Game_Matrix->FindAsh()->jpuff) {

		for (int i = 0; i < AllFinElements.size(); i++) {
			if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
				AllFinElements[i]->GetMonsterFromElements()->PauseMonster();
				Game_Matrix->FindAsh()->jpuff = false;
				//break;
			}
		}
		j = true;
		time(&jpuff_timer);
	}
	
	if (Game_Matrix->FindAsh()->zoroark) {

		for (int i = 0; i < AllFinElements.size(); i++) {
			if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
				AllFinElements[i]->GetMonsterFromElements()->TurnMonsterPowerless();
				Game_Matrix->FindAsh()->zoroark = false;
			}
		}
		z = true;
		time(&zoroark_timer);
	}


}



void CheckAbilityTime(Matrix* Game_Matrix, map<string, Texture*> AllTextures , time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer, bool &s, bool &j, bool &g, bool &z, double timelimit) {
	time_t endt;

	if (s) {
		if (difftime(time(&endt), squirtle_timer) >= 2*timelimit) {
			//exit(0);
			Summoner.SummonOneMonster(0, 0, AllTextures, AllFinElements);
			
			s = false;
		}
	}

	if (j) {
		if (difftime(time(&endt), jpuff_timer) >= timelimit) {
			for (int i = 0; i < AllFinElements.size(); i++) {
				if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
					AllFinElements[i]->GetMonsterFromElements()->ResumeMonster();
				}
			}
			j = false;
		}
	}

	if (z) {
		if (difftime(time(&endt), zoroark_timer) >= timelimit) {
			for (int i = 0; i < AllFinElements.size(); i++) {
				if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
					AllFinElements[i]->GetMonsterFromElements()->TurnMonsterPowerful();
				}
			}
			z = false;
		}
	}

	if (g) {
		if (difftime(time(&endt), gastly_timer) >= timelimit) {
			for (int i = 0; i < AllFinElements.size(); i++) {
				if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
					AllFinElements[i]->GetMonsterFromElements()->RemoveConfusion();
				}
			}
			g = false;
		}
	}
}


void GameRun(SDL_Event game_event, int &player1_score, int &player2_score, int playernum,  TTF_Font* game_font, map<string, Texture*> AllTextures) {

	SDL_Rect ScoreVals = { 0,0, 300, 30 };
	Texture* score_texture = new Texture();

	bool run2 = true;
	
	time_t squirtle_timer;
	time_t jpuff_timer ;
	time_t zoroark_timer ;
	time_t gastly_timer;

	bool jpuff_on = false;
	bool gastly_on = false;
	bool zoroark_on = false;
	bool squirtle_on = false;
	
	
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


		if (Game_Matrix.FindAsh() == NULL) {
			break;
		}

		int ability_boost = 0;
		if (playernum == 1) {
			ability_boost = player1_score;
		}
		else {
			ability_boost = player2_score;
		}

		AbilityAction(&Game_Matrix,squirtle_timer, jpuff_timer, zoroark_timer, gastly_timer,squirtle_on, jpuff_on, zoroark_on, gastly_on);
		CheckAbilityTime(&Game_Matrix, AllTextures, squirtle_timer, jpuff_timer, zoroark_timer,gastly_timer, squirtle_on, jpuff_on, zoroark_on, gastly_on, 5 + ability_boost/100 );


		SDL_RenderClear(Game_Renderer);



		for (int i = 0; i < AllFinElements.size(); i++) {
			//AllFinElements[i]->Refresh();
			AllFinElements[i]->Render();
		}

		if (playernum == 1) {
			player1_score = Ash::points;
		}
		else {
			player2_score = Ash::points;
		}

		score_texture->LoadText(game_font, game_textcolor, "Ankita's score : " + to_string(player1_score));
		score_texture->Render(50 + 200, 15, &ScoreVals, 0.0, NULL, SDL_FLIP_NONE);
		score_texture->LoadText(game_font, game_textcolor, "Aryan's score : " + to_string(player2_score));
		score_texture->Render(420 + 200, 15, &ScoreVals, 0.0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(Game_Renderer);


	}
}





void RendertoLoc(SDL_Renderer* Game_Renderer,const char* loc,  int x, int y, int w , int h) {
	SDL_Rect rectangle;
	
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w =w;
	rectangle.h = h;
	SDL_Surface* tempsur = SDL_LoadBMP(loc);
	SDL_Texture* Teex = SDL_CreateTextureFromSurface(Game_Renderer, tempsur);
	SDL_RenderCopy(Game_Renderer, Teex, NULL, &rectangle);
}


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
	bool run2 = true;

	
	Texture* illumi_texture = new Texture();
	illumi_texture->LoadImage("pol.bmp");


	RendertoLoc(Game_Renderer, "m.bmp", 0, 0, WIDTH, HEIGHT);
	RendertoLoc(Game_Renderer, "pol.bmp", 200, 100, 800, 200);
	RendertoLoc(Game_Renderer, "pik.bmp", 450, 400, 400, 300);

	while (run) {

		

		SDL_RenderPresent(Game_Renderer);
		
		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN) {
				run = false;
			}

			if (game_event.type == SDL_QUIT) {
				run = false;
				run2 = false;
			}
		}

	}
	
	int player1_score = 0;
	int player2_score = 0;
	
	
	GameRun(game_event, player1_score, player2_score,1,  game_font, TextureHash);
	

	
	//AllFinElements.erase(AllFinElements.begin(), AllFinElements.end()--);

	run = true;
	RendertoLoc(Game_Renderer, "m.bmp", 0, 0, WIDTH, HEIGHT);
	RendertoLoc(Game_Renderer, "pol.bmp", 200, 100, 800, 200);
	RendertoLoc(Game_Renderer, "pik.bmp", 450, 400, 400, 300);

	while (run) {



		SDL_RenderPresent(Game_Renderer);

		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN) {
				run = false;
			}

			if (game_event.type == SDL_QUIT) {
				run = false;
				run2 = false;
			}
		}

	}

	
	Summoner.EmptyAll();
	Summoner.SummonFromMap("map.txt", TextureHash);
	Summoner.SummonAll(AllFinElements);

	Ash::points = 0;
	run2 = true;

	GameRun(game_event, player1_score, player2_score, 2, game_font, TextureHash);
	
	//Update the surface
	
	//SDL_Delay(10000);
	return 0;
}
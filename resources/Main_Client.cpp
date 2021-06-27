
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
#include <WS2tcpip.h>
#include<iostream>
#include<string>
//using namespace std;

#pragma comment(lib,"ws2_32.lib") //Winsock Library

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

SDL_Event StringToKeyEvent(string s) {

	SDL_Event finev;

	if (s == "000") {
		finev.key.keysym.sym = SDLK_UP;
	}
	else if (s == "001")
	{
		finev.key.keysym.sym = SDLK_DOWN;
	}
	else if (s == "010")
	{
		finev.key.keysym.sym = SDLK_LEFT;
	}
	else if (s == "011")
	{
		finev.key.keysym.sym = SDLK_RIGHT;
	}

	return finev;


}

string KeyEventtoString(SDL_Event s) {

	string finhash = "";

	if (s.type == SDL_KEYDOWN && s.key.repeat == 0)
	{
		if (s.key.keysym.sym == SDLK_UP || s.key.keysym.sym == SDLK_w)
		{
			finhash = "000";
		}
		else if (s.key.keysym.sym == SDLK_DOWN || s.key.keysym.sym == SDLK_s)
		{
			finhash = "001";
		}
		else if (s.key.keysym.sym == SDLK_LEFT || s.key.keysym.sym == SDLK_a)
		{
			finhash = "010";
		}
		else if (s.key.keysym.sym == SDLK_RIGHT || s.key.keysym.sym == SDLK_d)
		{
			finhash = "011";
		}
	}

	return finhash;

}

void AbilityAction(Matrix* Game_Matrix, time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer, bool& s, bool& j, bool& g, bool& z) {

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
		time(&gastly_timer);
	}

	if (Game_Matrix->FindAsh()->jpuff) {

		for (int i = 0; i < AllFinElements.size(); i++) {
			if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
				AllFinElements[i]->GetMonsterFromElements()->PauseMonster();
				//break;
			}
		}
		Game_Matrix->FindAsh()->jpuff = false;
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



void CheckAbilityTime(Matrix* Game_Matrix, map<string, Texture*> AllTextures, time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer, bool& s, bool& j, bool& g, bool& z, double timelimit) {
	time_t endt;

	if (s) {
		if (difftime(time(&endt), squirtle_timer) >= 2 * timelimit) {
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


//SDL_UP = 000
//SDL_DOWN = 001
//SDL_LEFT = 010
//SDL_RIGHT = 011






void GameRun(SDL_Event game_event, SOCKET sock,  int& player1_score, int& player2_score, int playernum, TTF_Font* game_font, map<string, Texture*> AllTextures) {

	SDL_Rect ScoreVals = { 0,0, 300, 30 };
	Texture* score_texture = new Texture();

	char buf[4096];
	string userInput;

	
			
	

	bool run2 = true;

	time_t squirtle_timer;
	time_t jpuff_timer;
	time_t zoroark_timer;
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

		int bytesReceived = recv(sock, buf, 4096, 0);
		string s = "";

		char* message;

		if (playernum == 1) {
			if (bytesReceived > 0)
			{
				s = string(buf, 0, bytesReceived);
			}

			game_event = StringToKeyEvent(s);

			if (game_event.type == SDL_QUIT) {
				run2 = false;
			}

			for (int i = 0; i < AllFinElements.size(); i++) {
				AllFinElements[i]->HandleKeys(&game_event);
			}
		}
		else
		{

			while (SDL_PollEvent(&game_event) != 0) {
				if (game_event.type == SDL_QUIT) {
					run2 = false;
				}

				for (int i = 0; i < AllFinElements.size(); i++) {
					AllFinElements[i]->HandleKeys(&game_event);
				}
			}

			message = (char*) KeyEventtoString(&game_event);
			send(new_socket, message, strlen(message), 0);

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

		AbilityAction(&Game_Matrix, squirtle_timer, jpuff_timer, zoroark_timer, gastly_timer, squirtle_on, jpuff_on, zoroark_on, gastly_on);
		CheckAbilityTime(&Game_Matrix, AllTextures, squirtle_timer, jpuff_timer, zoroark_timer, gastly_timer, squirtle_on, jpuff_on, zoroark_on, gastly_on, 5 + ability_boost / 100);


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
		score_texture->Render(50 + 200, 15, 0.0, SDL_FLIP_NONE, &ScoreVals, NULL);
		score_texture->LoadText(game_font, game_textcolor, "Aryan's score : " + to_string(player2_score));
		score_texture->Render(420 + 200, 15, 0.0, SDL_FLIP_NONE, &ScoreVals, NULL);
		SDL_RenderPresent(Game_Renderer);


	}
}





void RendertoLoc(SDL_Renderer* Game_Renderer, const char* loc, int x, int y, int w, int h) {
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	SDL_Surface* tempsur = SDL_LoadBMP(loc);
	SDL_Texture* Teex = SDL_CreateTextureFromSurface(Game_Renderer, tempsur);
	SDL_RenderCopy(Game_Renderer, Teex, NULL, &rectangle);
}




int main(int argc, char* argv[]) {


	TTF_Init();

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 8888;

	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}


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
	wall_texture->LoadImageFromPath("wall.bmp");

	Texture* ash_texture = new Texture();
	ash_texture->LoadImageFromPath("ash.bmp");

	Texture* gastly_texture = new Texture();
	gastly_texture->LoadImageFromPath("gastly.bmp");

	Texture* pokeball_texture = new Texture();
	pokeball_texture->LoadImageFromPath("pokeball.bmp");

	Texture* zoroark_texture = new Texture();
	zoroark_texture->LoadImageFromPath("zoroark.bmp");

	Texture* squirtle_texture = new Texture();
	squirtle_texture->LoadImageFromPath("squirtle.bmp");

	Texture* jigglypuff_texture = new Texture();
	jigglypuff_texture->LoadImageFromPath("jigglypuff.bmp");

	Texture* monster_texture = new Texture();
	monster_texture->LoadImageFromPath("monster.bmp");



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
	illumi_texture->LoadImageFromPath("pol.bmp");


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

	ServerRun();


	char buf[4096];
	string userInput;

	

	int player1_score = 0;
	int player2_score = 0;


	GameRun(game_event, sock, player1_score, player2_score, 1, game_font, TextureHash);



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

	GameRun(game_event,sock, player1_score, player2_score, 2, game_font, TextureHash);

	//Update the surface

	//SDL_Delay(10000);
	return 0;
}

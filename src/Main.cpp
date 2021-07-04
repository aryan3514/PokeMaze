#include <bitset>
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
#include "Maze.h"
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
#include <vector>
//using namespace std;



#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

const int WIDTH = 1250;
const int HEIGHT = 800;


vector <tuple<int, string >> players;

SDL_Texture* ShowImages[11];

SDL_Window* Game_Window = NULL;
SDL_Renderer* Game_Renderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* Game_s = NULL;
SDL_Texture* Tex = NULL;
TTF_Font* game_font;

Matrix Game_Matrix(30, 30);

Maze Game_Maze;

Summon Summoner(&Game_Matrix);

vector <Element*> AllFinElements;

SDL_Color game_textcolor = { 255,255, 255 };


SDL_Event game_event;

bool ONLINE = false;
int OFFLINE_PLAYER_NUMBER = 2;

WSADATA wsa;
SOCKET sock;
struct sockaddr_in server, client;
int c;
int myplayernum;

string LocationToString() {

	int x = Game_Matrix.FindAsh()->GetPos().x;
	int y = Game_Matrix.FindAsh()->GetPos().y;
	int tx = Game_Matrix.FindAsh()->curunit->GetPos().x;
	int ty = Game_Matrix.FindAsh()->curunit->GetPos().x;
	string s = "";

	s += (bitset<12>(x)).to_string();
	s += (bitset<12>(y)).to_string();
	//s += (bitset<6>(tx)).to_string();
	//s += (bitset<6>(ty)).to_string();

	for (int i = 0; i < AllFinElements.size(); i++) {
		if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
			int mx = AllFinElements[i]->GetMonsterFromElements()->position.x;
			int my = AllFinElements[i]->GetMonsterFromElements()->position.y;
			int mtx = AllFinElements[i]->GetMonsterFromElements()->curunit->GetPos().x;
			int mty = AllFinElements[i]->GetMonsterFromElements()->curunit->GetPos().y;
			s += (bitset<12>(mx)).to_string();
			s += (bitset<12>(my)).to_string();
			//s += (bitset<6>(mtx)).to_string();
			//s += (bitset<6>(mty)).to_string();
		}
	}

	return s;

}

void StringToLocation(string s) {

	int arr[16];

	for (int i = 0; i < 4; i++) {
		arr[0 + 2 * i] = stoi(s.substr(0 + 24 * i, 12), 0, 2);
		arr[1 + 2 * i] = stoi(s.substr(12 + 24 * i, 12), 0, 2);
		//arr[2 + 4*i] = stoi(s.substr(24 + 36*i, 6), 0, 2);
		//arr[3 + 4*i] = stoi(s.substr(30 + 36*i, 6), 0, 2);
	}
	Game_Matrix.FindAsh()->position.x = arr[0];
	Game_Matrix.FindAsh()->position.y = arr[1];
	//Game_Matrix.FindAsh()->curunit->pos.x = arr[2];
	//Game_Matrix.FindAsh()->curunit->pos.y = arr[3];

	int k = 1;
	for (int i = 0; i < AllFinElements.size(); i++) {
		if (AllFinElements[i]->GetMonsterFromElements() != NULL) {
			AllFinElements[i]->GetMonsterFromElements()->position.x = arr[2 * k];
			AllFinElements[i]->GetMonsterFromElements()->position.y = arr[2 * k + 1];
			//AllFinElements[i]->GetMonsterFromElements()->nextunit = Game_Matrix.GetUnitFromMatrix(arr[4 * k + 2], arr[4 * k + 3]);

				//pos.x = arr[4 * k + 2];
			//AllFinElements[i]->GetMonsterFromElements()->curunit->pos.y = arr[4 * k + 3];
			k++;
		}
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
	//SDL_SetTextureBlendMode(Teex, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureAlphaMod(Teex, 50);
	SDL_RenderCopy(Game_Renderer, Teex, NULL, &rectangle);
}

void RendertoLocc(SDL_Renderer* Game_Renderer, SDL_Texture* teex, int x, int y, int w, int h) {
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	//SDL_Surface* tempsur = SDL_LoadBMP(loc);

	//SDL_SetTextureBlendMode(Teex, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureAlphaMod(Teex, 50);
	SDL_RenderCopy(Game_Renderer, teex, NULL, &rectangle);
}

void RendertoSide(SDL_Renderer* Game_Renderer, SDL_Texture* loc) {
	RendertoLocc(Game_Renderer, loc, 20, 330, 150, 150);
	//RendertoLoc(Game_Renderer, loc, 20, 10, 150, 150);
	RendertoLocc(Game_Renderer, loc, 20, 160, 150, 150);
	RendertoLocc(Game_Renderer, loc, 20, 500, 150, 150);
	//RendertoLoc(Game_Renderer, loc, 20, 650, 150, 150);

	RendertoLocc(Game_Renderer, loc, 1090, 330, 150, 150);
	//RendertoLoc(Game_Renderer, loc, 1090, 10, 150, 150);
	RendertoLocc(Game_Renderer, loc, 1090, 160, 150, 150);
	RendertoLocc(Game_Renderer, loc, 1090, 500, 150, 150);
	//RendertoLoc(Game_Renderer, loc, 1090, 650, 150, 150);
}




void AbilityAction(Matrix* Game_Matrix, time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer, bool& s, bool& j, bool& g, bool& z) {

	if (Game_Matrix->FindAsh()->squrtle) {

		//RendertoSide(Game_Renderer, "bigsquirtle.bmp");

		//SDL_RenderPresent(Game_Renderer);


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



void CheckAbilityTime(Matrix* Game_Matrix, map<string, Texture*> AllTextures, SDL_Texture* ar[], time_t& squirtle_timer, time_t& jpuff_timer, time_t& zoroark_timer, time_t& gastly_timer, bool& s, bool& j, bool& g, bool& z, double timelimit) {
	time_t endt;

	if (s) {
		if (difftime(time(&endt), squirtle_timer) >= 2 * timelimit) {
			//exit(0);
			Summoner.SummonOneMonster(0, 0, AllTextures, AllFinElements, "monster");

			s = false;
		}
		else {
			RendertoSide(Game_Renderer, ar[0]);
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
		else {
			RendertoSide(Game_Renderer, ar[1]);
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
		else {
			RendertoSide(Game_Renderer, ar[2]);
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
		else {
			RendertoSide(Game_Renderer, ar[3]);
		}
	}
}

void Wait(SDL_Event* e, SDL_Texture* arr) {
	bool run = true;

	while (run) {
		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN) {
				SDL_Delay(150);
				run = false;
				//exit(0);
			}
			else if (game_event.type == SDL_QUIT) {
				exit(0);
			}
		}

		RendertoLocc(Game_Renderer, arr, 0, 0, WIDTH, HEIGHT);
		SDL_RenderPresent(Game_Renderer);
	}
}

void NameAndIntro(SDL_Event game_event, int playernum, TTF_Font* game_font, map<string, Texture*> AllTextures, SDL_Texture* ShowImages[]) {



	if ((myplayernum != playernum) && ONLINE) {
		Wait(&game_event, ShowImages[10]);
		players.push_back(tuple<int, string>(0, "online_player"));
		return;
	}



	string inputText = "Enter your name : ";
	string player_name = "";

	SDL_Color text_color = { 0, 0, 0, 0xFF };
	Texture* instr_texture = new Texture();
	Texture* name_texture = new Texture();

	instr_texture->LoadText(game_font, text_color, (inputText).c_str());

	bool render_name = true;

	bool run = true;
	SDL_Rect NameVals = { 0,0, 400, 50 };

	RendertoLocc(Game_Renderer, ShowImages[0], 0, 0, WIDTH, HEIGHT);
	RendertoLocc(Game_Renderer, ShowImages[1], 200, 50, 800, 200);
	RendertoLocc(Game_Renderer, ShowImages[2], 450, 400, 400, 300);

	instr_texture->Render(300, 300, 0.0, SDL_FLIP_NONE, &NameVals, NULL);

	while (run) {

		SDL_RenderPresent(Game_Renderer);

		SDL_Rect PalVals = { 0,0, player_name.length() * 20, 50 };

		SDL_StartTextInput();
		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN) {
				run = false;
			}
			else if (game_event.key.keysym.sym == SDLK_BACKSPACE && player_name.length() > 0)
			{
				//lop off character
				player_name.pop_back();
				render_name = true;
			}
			else if (game_event.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!(SDL_GetModState() & KMOD_CTRL && (game_event.text.text[0] == 'c' || game_event.text.text[0] == 'C' || game_event.text.text[0] == 'v' || game_event.text.text[0] == 'V')))
				{
					//Append character
					player_name += game_event.text.text;
					render_name = true;
				}
			}

			if (render_name)
			{
				//Text is not empty
				if (inputText != "")
				{
					name_texture->LoadText(game_font, text_color, (player_name).c_str());
				}
				else
				{
					name_texture->LoadText(game_font, text_color, " ");
				}

			}


			//if (playernum == 2) exit(0);
			SDL_RenderClear(Game_Renderer);
			RendertoLocc(Game_Renderer, ShowImages[0], 0, 0, WIDTH, HEIGHT);
			RendertoLocc(Game_Renderer, ShowImages[1], 200, 50, 800, 200);
			RendertoLocc(Game_Renderer, ShowImages[2], 450, 400, 400, 300);
			instr_texture->Render(300, 300, 0.0, SDL_FLIP_NONE, &NameVals, NULL);
			name_texture->Render(700, 300, 0.0, SDL_FLIP_NONE, &PalVals, NULL);
			SDL_RenderPresent(Game_Renderer);


			if (game_event.type == SDL_QUIT) {
				exit(0);
			}
		}

	}

	players.push_back(tuple<int, string>(0, player_name));
}

void GameRun(SDL_Event game_event, int playernum, TTF_Font* game_font, map<string, Texture*> AllTextures) {

	SDL_Rect ScoreVals = { 0,0, 350, 30 };
	Texture* score_texture = new Texture();

	bool run2 = true;

	time_t squirtle_timer;
	time_t jpuff_timer;
	time_t zoroark_timer;
	time_t gastly_timer;

	bool jpuff_on = false;
	bool gastly_on = false;
	bool zoroark_on = false;
	bool squirtle_on = false;

	bool isDone = false;


	SDL_Texture* BigTexArray[4];
	BigTexArray[0] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/skins/bigsquirtle.bmp"));
	BigTexArray[1] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/skins/bigpuff.bmp"));
	BigTexArray[2] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/skins/bigzor.bmp"));
	BigTexArray[3] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/skins/biggastly.bmp"));


	int data_ar[16];

	char buf[1024];
	string userInput;

	string s = "";

	char* message;


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




		if (playernum == myplayernum) {
			while (SDL_PollEvent(&game_event) != 0) {
				if (game_event.type == SDL_QUIT) {
					run2 = false;
				}

				for (int i = 0; i < AllFinElements.size(); i++) {
					AllFinElements[i]->HandleKeys(&game_event);
				}
			}

			if (ONLINE) {
				string str_obj(LocationToString());
				message = &str_obj[0];
				send(sock, message, strlen(message), 0);
			}

			


			for (int i = 0; i < AllFinElements.size(); i++) {
				AllFinElements[i]->Refresh();
				if (AllFinElements[i]->isPokeball()) {
					isDone = true;
				}
			}
		}
		else
		{
			isDone = true;
			int bytesReceived = recv(sock, buf, 1024, 0);
			if (bytesReceived > 0)
			{
				//cout << s << endl;
				s = string(buf, 0, bytesReceived);

				if (s == "end") {
					break;
				}
				if (s.length() == 96) {
					StringToLocation(s);
					//SetAll(data_ar);

					for (int i = 0; i < AllFinElements.size(); i++) {
						AllFinElements[i]->ViewRefresh();
						//AllFinElements[i]->Render();
					}
				}



			}

		}





		if (Game_Matrix.FindAsh() == NULL || !isDone) {
			if (ONLINE) {
				string str_obj("end");
				message = &str_obj[0];
				send(sock, message, strlen(message), 0);
			}
			
			SDL_RenderClear(Game_Renderer);
			break;
		}

		get<0>(players[playernum - 1]) = Ash::points;

		int ability_boost = get<0>(players[playernum - 1]);

		AbilityAction(&Game_Matrix, squirtle_timer, jpuff_timer, zoroark_timer, gastly_timer, squirtle_on, jpuff_on, zoroark_on, gastly_on);
		SDL_RenderClear(Game_Renderer);
		CheckAbilityTime(&Game_Matrix, AllTextures, BigTexArray, squirtle_timer, jpuff_timer, zoroark_timer, gastly_timer, squirtle_on, jpuff_on, zoroark_on, gastly_on, 5 + ability_boost / 100);



		for (int i = 0; i < AllFinElements.size(); i++) {
			//AllFinElements[i]->Refresh();
			AllFinElements[i]->Render();
		}



		score_texture->LoadText(game_font, game_textcolor, get<1>(players[playernum - 1]) + "'s score : " + to_string(get<0>(players[playernum - 1])));
		score_texture->Render(200, 15, 0.0, SDL_FLIP_NONE, &ScoreVals, NULL);
		//score_texture->LoadText(game_font, game_textcolor, player2_name + "'s score : " + to_string(player2_score));
		//score_texture->Render(470 + 200, 15, 0.0 , SDL_FLIP_NONE, &ScoreVals,  NULL);
		SDL_RenderPresent(Game_Renderer);


	}
}


void LoadImagesinBulk() {
	ShowImages[0] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/m.bmp"));
	ShowImages[1] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/pol.bmp"));
	ShowImages[2] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/skins/pik.bmp"));
	ShowImages[3] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("biggastly.bmp"));
	ShowImages[4] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/1.bmp"));
	ShowImages[5] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/2.bmp"));
	ShowImages[6] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/3.bmp"));
	ShowImages[7] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/4.bmp"));
	ShowImages[8] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/5.bmp"));
	ShowImages[9] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/6.bmp"));
	ShowImages[10] = SDL_CreateTextureFromSurface(Game_Renderer, SDL_LoadBMP("resources/screens/7.bmp"));
}


void Initialise() {


	TTF_Init();

	int t;
	cout << "-------------------------------------------------------" << endl;
	cout << "Do you want to play the game online [0] / offline [1] (default) ? " << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "(Warning : If you choose the online mode, make sure that the server is running, and it is accepting connections right now! )" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "Enter \"0\" for online mode or \"1\" for offline mode : " << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "(If you enter anything other than 0 or 1, the game will run in the offline mode)" << endl;;
	cout << "-------------------------------------------------------" << endl;
	cout << "Waiting for input : ";
	cin >> t;
	if (t == 0) {
		ONLINE = true;
	}
	else
	{
		ONLINE = false;
		int n;
		cout << "Enter the number of players : ";
		cin >> n;
		OFFLINE_PLAYER_NUMBER = n;
	}


	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		exit(0);
	}

	


	game_font = TTF_OpenFont("resources/font/renbow.ttf", 35);

	

	if (game_font == NULL) {
		cout << "HI" << endl;
		exit(0);
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
}


void LoadAllTextures(map<string, Texture*>& TextureHash, bool ash) {
	Texture* wall_texture = new Texture();
	wall_texture->LoadImageFromPath("resources/skins/wall.bmp");

	Texture* ash_texture = new Texture();
	ash_texture->LoadImageFromPath("resources/skins/ash.bmp");

	Texture* gastly_texture = new Texture();
	gastly_texture->LoadImageFromPath("resources/skins/gastly.bmp");

	Texture* pokeball_texture = new Texture();
	pokeball_texture->LoadImageFromPath("resources/skins/pokeball.bmp");

	Texture* zoroark_texture = new Texture();
	zoroark_texture->LoadImageFromPath("resources/skins/zoroark.bmp");

	Texture* squirtle_texture = new Texture();
	squirtle_texture->LoadImageFromPath("resources/skins/squirtle.bmp");

	Texture* jigglypuff_texture = new Texture();
	jigglypuff_texture->LoadImageFromPath("resources/skins/jigglypuff.bmp");

	Texture* monster_texture = new Texture();
	monster_texture->LoadImageFromPath("resources/skins/monster.bmp");

	if (ash) ash_texture->LoadImageFromPath("resources/skins/ash.bmp");
	else ash_texture->LoadImageFromPath("resources/skins/misty.bmp");

	TextureHash.insert(pair<string, Texture*>("wall", wall_texture));
	TextureHash.insert(pair<string, Texture*>("ash", ash_texture));
	TextureHash.insert(pair<string, Texture*>("gastly", gastly_texture));
	TextureHash.insert(pair<string, Texture*>("pokeball", pokeball_texture));
	TextureHash.insert(pair<string, Texture*>("zoroark", zoroark_texture));
	TextureHash.insert(pair<string, Texture*>("squirtle", squirtle_texture));
	TextureHash.insert(pair<string, Texture*>("jigglypuff", jigglypuff_texture));
	TextureHash.insert(pair<string, Texture*>("monster", monster_texture));
}

void LoadAndConnectToClient() {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		//return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	string ipAddress = "127.0.0.1";

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(8888);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		exit(0);
	}

	cout << "Connected" << endl;
}


void PostGameDisplay() {

	if (ONLINE) {
		string str_obj("p" + get<1>(players[myplayernum - 1]) +"|"+ to_string(get<0>(players[myplayernum - 1])));
		char* message = &str_obj[0];
		//cout << strlen(message) << endl;
		send(sock, message, strlen(message), 0);

		players.erase(players.begin(), players.end());
		char buff[1024];
		int beet = recv(sock, buff, sizeof(buff), 0);


		while (string(buff, 0, beet).substr(0, 3) != "end") {
			if (string(buff, 0, beet).at(0) == 'p') {
				string sre = string(buff, 0, beet);
				string name = "online_player";
				int score = 0;
				for (int i = 1; i < sre.length(); i++) {
					if ((sre.at(i))=='|') {
						name = (sre.substr(1, i - 1));
						score = stoi(sre.substr(i+1, sre.length() - i-1));
						break;
					}
				}
				players.push_back(tuple<int, string>(score, name));
			}
			int beet = recv(sock, buff, sizeof(buff), 0);
		}
	}
	
	

	sort(players.begin(), players.end());
	reverse(players.begin(), players.end());
	SDL_RenderClear(Game_Renderer);
	//SDL_SetRenderDrawColor(Game_Renderer, 255, 0, 0, 255);

	vector<Texture*> pnames_textures;
	for (int i = 0; i < players.size(); i++) {
		Texture* pname = new Texture();
		string lk = to_string(i + 1)+ ". " + get<1>(players[i]);
		if (get<1>(players[i]).size() < 18) {
			for (int k = 0; k < 22 - get<1>(players[i]).size(); k++) {
				lk += " ";
			}
		}
		pname->LoadText(game_font, game_textcolor, lk);
		pnames_textures.push_back(pname);
	}

	vector<Texture*> pscore_textures;
	for (int i = 0; i < players.size(); i++) {
		Texture* pscore_texture = new Texture();
		pscore_texture->LoadText(game_font, game_textcolor, to_string(get<0>(players[i])));
		pscore_textures.push_back(pscore_texture);
	}

	SDL_Rect rec = { 0,0,400,40 };
	SDL_Rect recc = { 0,0,50,40 };

	RendertoLocc(Game_Renderer, ShowImages[6], 0, 0, WIDTH, HEIGHT);
	for (int i = 0; i < players.size(); i++) {
		pnames_textures[i]->Render(350, 100 + (i + 1) * 40, 0.0, SDL_FLIP_NONE, &rec, NULL);
		pscore_textures[i]->Render(850, 100 + (i + 1) * 40, 0.0, SDL_FLIP_NONE, &recc, NULL);
	}

	bool run = true;
	while (run) {
		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN) {
				SDL_Delay(150);
				run = false;
				//exit(0);
			}
			else if (game_event.type == SDL_QUIT) {
				exit(0);
			}
		}

		SDL_RenderPresent(Game_Renderer);
	}
}





int main(int argc, char* argv[]) {

	srand(time(0));
	
	Initialise();


	Element::Element_Matrix = &Game_Matrix;
	
	Game_Maze.GenerateLabryinth(rand()%23, rand()%23);
	
	Game_Maze.StoreMaze();


	if (ONLINE) {
		LoadAndConnectToClient();

		char buf[1024];
		string userInput;

		string ss = "";

		int bytes_rec;
		while (true)
		{
			bytes_rec = recv(sock, buf, 1024, 0);
			if (bytes_rec > 0) {
				ss = string(buf, 0, bytes_rec);
				break;
			}
		}

		myplayernum = stoi(ss, 0, 2);

		if (myplayernum == 1) {

			string mez = "";
			string myText = "";
			ifstream MyReadFile("map.txt");

			// Use a while loop together with the getline() function to read the file line by line
			while (getline(MyReadFile, myText)) {
				mez += myText;
				//mez += "/n";
			}

			// Close the file
			MyReadFile.close();
			string str_obj(mez);
			const char* mesz = &str_obj[0];
			send(sock, mesz, strlen(mesz), 0);
		}
		else {
			while (true)
			{
				bytes_rec = recv(sock, buf, 1024, 0);
				if (bytes_rec > 0) {
					ss = string(buf, 0, bytes_rec);
					ofstream MyFile("map.txt");

					for (int i = 0; i < 30; i++) {
						MyFile << ss.substr(30*i,30);
						MyFile << "\n";
					}
					//MyFile << ss;

					MyFile.close();
					break;
				}
			}

			
		}

	}
	



	LoadImagesinBulk();

	Wait(&game_event, ShowImages[7]);

	bool run = true;
	bool ash = true;
	while (run) {
		while (SDL_PollEvent(&game_event) != 0) {
			if (game_event.key.keysym.sym == SDLK_RETURN || game_event.key.keysym.sym == SDLK_a) {
				SDL_Delay(150);
				run = false;
				//exit(0);
			}
			else if (game_event.key.keysym.sym == SDLK_m) {
				ash = false;;
				SDL_Delay(150);
				run = false;
			}
		}

		RendertoLocc(Game_Renderer, ShowImages[9], 0, 0, WIDTH, HEIGHT);
		SDL_RenderPresent(Game_Renderer);
	}
	map<string, Texture*> TextureHash;

	LoadAllTextures(TextureHash, ash);

	Summoner.SummonFromMap("map.txt", TextureHash);
	Summoner.SummonAll(AllFinElements);

	Wait(&game_event, ShowImages[5]);

	Wait(&game_event, ShowImages[4]);

	Wait(&game_event, ShowImages[8]);
	int l = OFFLINE_PLAYER_NUMBER;
	const char* message;
	char buff[1024];
	if (ONLINE) {
		
		int bet = recv(sock, buff, sizeof(buff), 0);

		while (string(buff, 0, bet).at(0) != 'p') {
			bet = recv(sock, buff, sizeof(buff), 0);
		}

		l = stoi(string(buff, 0, bet).substr(1, string(buff, 0, bet).length() - 1));
	}
	int playernum = 1;

	
	while (l--) {


		NameAndIntro(game_event, playernum, game_font, TextureHash, ShowImages);

		if (ONLINE) {
			string str_obj("start");
			message = &str_obj[0];
			send(sock, message, strlen(message), 0);

			char buff[1024];
			int beet = recv(sock, buff, sizeof(buff), 0);

			while (string(buff, 0, beet).substr(0, 6) != "start" + to_string(playernum - 1)) {
				beet = recv(sock, buff, sizeof(buff), 0);
				//continue;%
			}
		}
		else
		{
			myplayernum = playernum;
		}
		


		GameRun(game_event, playernum, game_font, TextureHash);



		SDL_RenderClear(Game_Renderer);
		Summoner.EmptyAll();
		Summoner.SummonFromMap("map.txt", TextureHash);
		Summoner.SummonAll(AllFinElements);
		Ash::points = 0;
		playernum++;
	}

	PostGameDisplay();
	
	closesocket(sock);
	WSACleanup();
	return 0;
}
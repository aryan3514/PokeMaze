#include "Maze.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

Maze::Maze() {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			maze[i][j].myrow = j;
			maze[i][j].mycol = i;
		}
	}
}

void Maze::DisplayMaze() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {


			if (maze[i][j].isWall) {
				cout << "p";
			}
			else
			{
				cout << "w";
			}
		}
		cout << endl;
	}
}

void Maze::StoreMaze() {
	string s = "";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
	
			if (maze[i][j].isWall) {
				s += "p";
			}
			else
			{
				s += "w";
			}
		}
		s += "\n";
	}

	cout << (s.size()) << endl;;

	for (int i = 0; i < 30; i++) {
		s.at(i) = 'w';
		s.at(682 + i) = 'w';
	}

	for (int i = 0; i < 23; i++) {
		s.at(31 * i) = 'w';
		s.at(31 * i + 29) = 'w';
	}

	//SQUIRTLES
	for (int i = 0; i < 2; i++) {
		int randx = rand() % 690;
		while (randx == 30 || randx%31==30) {
			randx = rand() % 690;
		}
		s.at(randx) = 's';
	}

	//ZOROARKS
	for (int i = 0; i < 3; i++) {
		int randx = rand() % 690;
		while (randx % 31 == 30 || randx == 30) {
			randx = rand() % 690;
		}
		s.at(randx) = 'z';
	}


	//JIGGLYPUFFS
	for (int i = 0; i < 3; i++) {
		int randx = rand() % 690;
		while (randx % 31 == 30 || randx ==30) {
			randx = rand() % 690;
		}
		s.at(randx) = 'j';
	}


	//GASTLYS
	for (int i = 0; i < 4; i++) {
		int randx = rand() % 690;
		while (randx % 31 == 30 || randx==30) {
			randx = rand() % 690;
		}
		s.at(randx) = 'g';
	}

	s.at(360) = 'a';
	


	s.at(0) = 'm';
	s.at(1) = 'm';
	s.at(2) = 'm';


	ofstream MyFile("map.txt");

	// Write to the file

	MyFile << s;

	// Close the file
	MyFile.close();

}

void Maze::GenerateLabryinth(int x, int y) {
	//vector<block*> mainstack;
	//vector<block*> neburs;

	srand(time(0));


	//mainstack.push_back(&maze[col][row]);

	block* curblock = &maze[y][x];
	int row = curblock->myrow; int col = curblock->mycol;
	curblock->visited = true;
	curblock->isWall = false;
	//block* anynebur = &maze[col][row];

	vector<string> dir = { "N", "W", "S","E" };
	int next_x = x;
	int next_y = y;

	int br_x = x;
	int br_y = y;

	while (dir.size() != 0) {
		int ind = rand() % dir.size();
		string bdir = dir[ind];
		vector<string>::iterator it = dir.begin();
		for (int i = 0; i < ind; i++) {
			it++;
		}
		dir.erase(it);

		if (bdir == "N" && y > 3) {
			next_y = y - 4;
			br_y = y - 1;

			if (maze[next_y][next_x].isWall) {
				maze[br_y][br_x].isWall = false;
				maze[br_y - 2][br_x].isWall = false;
				maze[br_y-3][br_x].isWall = false;
				GenerateLabryinth(next_x, next_y);
			}
		}

		if (bdir == "S" && y < height - 4) {
			next_y = y + 4;
			br_y = y + 1;

			if (maze[next_y][next_x].isWall) {
				maze[br_y][br_x].isWall = false;
				maze[br_y + 2][br_x].isWall = false;
				maze[br_y + 3][br_x].isWall = false;
				GenerateLabryinth(next_x, next_y);
			}
		}

		if (bdir == "E" && x < width - 4) {
			next_x = x + 4;
			br_x = x + 1;

			if (maze[next_y][next_x].isWall) {
				maze[br_y][br_x].isWall = false;
				maze[br_y][br_x + 2].isWall = false;
				maze[br_y][br_x+3].isWall = false;
				GenerateLabryinth(next_x, next_y);
			}
		}

		if (bdir == "W" && x > 3) {
			next_x = x - 4;
			br_x = x - 1;

			if (maze[next_y][next_x].isWall) {
				maze[br_y][br_x].isWall = false;
				maze[br_y][br_x - 2].isWall = false;
				maze[br_y][br_x - 3].isWall = false;
				GenerateLabryinth(next_x, next_y);
			}
		}


		/*if (maze[next_y][next_x].isWall) {
			maze[br_y][br_x].isWall = false;
			GenerateLabryinth(next_x, next_y);
		}*/
	}


	/*while (mainstack.size() != 0) {
		curblock = mainstack.back();
		mainstack.pop_back();

		int tempr = curblock->myrow;
		int tempc = curblock->mycol;

		if (tempr > 0 && !maze[tempc][tempr - 1].visited) {
			neburs.push_back(&maze[tempc][tempr - 1]);
		}

		if (tempc > 0 && !maze[tempc - 1][tempr].visited) {
			neburs.push_back(&maze[tempc - 1][tempr]);
		}

		if (tempr < width - 1 && !maze[tempc][tempr + 1].visited) {
			neburs.push_back(&maze[tempc][tempr + 1]);
		}

		if (tempc < height - 1 && !maze[tempc + 1][tempr].visited) {
			neburs.push_back(&maze[tempc + 1][tempr]);
		}

		if (neburs.size()!=0) {
			mainstack.push_back(curblock);
			anynebur = neburs[rand() % neburs.size()];
			anynebur->visited = true;
			anynebur->isWall = false;
			//cout << "Aryan" << endl;
			mainstack.push_back(anynebur);
			neburs.clear();
		}
	}*/
}
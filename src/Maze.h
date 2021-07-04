#pragma once
#include <vector>
#include <string>
class block {
public:
	int myrow;
	int mycol;
	bool visited = false;

	bool isWall = true;;

};

class Maze {
public:
	const static int width = 30;
	const static int height = 23;

	block maze[width][height];

	Maze();

	void DisplayMaze();

	void StoreMaze();

	void GenerateLabryinth(int x, int y);
};

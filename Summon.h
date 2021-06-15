#pragma once
#include "Matrix.h"
#include "Element.h"
#include <iostream>
#include <vector>
#include <map>
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
using namespace std;

class Summon {

public:
	Matrix* FinMatrix;

	vector<Element*>  AllElements;
	
	Summon(Matrix* Mat);

	bool SummonFromMap(string MapPath, map<string, Texture*> AllTextures);

	void SummonAll(vector <Element*> &AllGameElements);

	void SummonOneMonster(int x, int y, map<string, Texture*> AllTextures, vector <Element*>& AllGameElements);

	void EmptyAll();

};

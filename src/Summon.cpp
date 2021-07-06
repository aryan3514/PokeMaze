#include "Summon.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;

Summon::Summon(Matrix* Mat) {
	FinMatrix = Mat;
}

bool Summon::SummonFromMap(string MapPath, map<string, Texture*> AllTextures  ) {
	ifstream File(MapPath);
	string it;
	int x = 0;
	int y = 0;
	
	vector<Element*> tempmon; 
	while (getline(File, it)) {
		
		for (int i = 0; i < it.size(); i++) {
			
			
			Element* curel = NULL;
			Unit* uni = FinMatrix->GetUnitFromMatrix(i,y);

			if (it[i] == 'w') {
				curel = new Wall(uni, AllTextures.find("wall")->second);
			}
			else if (it[i] == 'a') {
				curel = new Ash(uni, AllTextures.find("ash")->second);
			}
			else if (it[i] == 'm') {
				curel = new Monster(uni, AllTextures.find("monster")->second);
			}
			else if (it[i] == 'p') {
				curel = new Pokeball(uni, AllTextures.find("pokeball")->second);
			}
			else if (it[i] == 'g') {
				curel = new Gastly(uni, AllTextures.find("gastly")->second);
			}
			else if (it[i] == 's') {
				curel = new Squirtle(uni, AllTextures.find("squirtle")->second);
			}
			else if (it[i] == 'z') {
				curel = new Zoroark(uni, AllTextures.find("zoroark")->second);
			}
			else if (it[i] == 'j') {
				curel = new JigglyPuff(uni, AllTextures.find("jigglypuff")->second);
			}

			if (curel != NULL && it[i] == 'm') tempmon.push_back(curel);
			
			if (curel != NULL && it[i]!='m') {
				AllElements.push_back(curel);
			}

			/*else {
				return false;
			}*/
		}
		y++;
	 }

	for (int i = 0; i < tempmon.size(); i++) {
		AllElements.push_back(tempmon[i]);
	}
	return true;

}


void Summon::SummonOneMonster(int x, int y, map<string, Texture*> AllTextures, vector <Element*>& AllGameElements, const char* loc) {
	Element* curel = NULL;
	Unit* uni = FinMatrix->GetUnitFromMatrix(x, y);
	curel = new Monster(uni, AllTextures.find(loc)->second);
	if (curel != NULL) {
		AllElements.push_back(curel);
	}
	AllGameElements.push_back(curel);

}

void Summon::EmptyAll() {
	AllElements.erase(AllElements.begin(), AllElements.end());
}

void Summon::SummonAll(vector <Element*> &AllGameElements){
	
	AllGameElements = AllElements;
}
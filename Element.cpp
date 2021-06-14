#include "Element.h"
#include <iostream>
using namespace std;

Matrix* Element::Element_Matrix = NULL;



void Element::HandleKeys(SDL_Event* event) {
	cout << "HandleKeys was not overriden" << endl;
}

void Element::Refresh() {
	cout << "Refresh was not overriden" << endl;
}

void Element::Render() {
	cout << "Render was not overriden" << endl;
}

void Element::Remove(){
	toRemove = true;
}

Monster* Element::GetMonsterFromElements() {
	return NULL;
}



#pragma once

#include "Matrix.h"

class Element {
public:
	static Matrix* Element_Matrix;
	bool toRemove;

	virtual void HandleKeys(SDL_Event* event);

	virtual void Refresh();

	virtual void Render();

	virtual void Remove();

};
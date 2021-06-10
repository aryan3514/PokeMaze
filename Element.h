#pragma once

#include "Matrix.h"

class Element {
public:
	static Matrix* Element_Matrix;
	bool toRemove = false;

	int width_offset = 175;
	int height_offset = 70;

	virtual void HandleKeys(SDL_Event* event);

	virtual void Refresh();

	virtual void Render();

	virtual void Remove();

};
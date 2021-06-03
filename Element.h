#pragma once

#include "Matrix.h"

class Element {
public:
	bool toRemove;

	virtual void HandleKeys(SDL_Event* event);

	virtual void Refresh();

	virtual void Render();

	virtual void Remove();

};
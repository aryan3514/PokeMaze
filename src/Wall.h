#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Unit.h"
#include "Element.h"

class Wall : public Element {
public:
    int width = 30;
    int height = 30;

    SDL_Point position;
    Unit* curunit;
    Texture* walltexture;
    SDL_Rect collider;

    Wall(Unit* Unitx, Texture* texture);

    void SetUnit(Unit* unitt);

    void Render();

    SDL_Rect GetCollider();

    Unit* GetCurUnit();

    SDL_Point GetPos();

};

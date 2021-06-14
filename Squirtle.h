
#pragma once
#include "Texture.h"
#include "Unit.h"
#include "Matrix.h"
#include "Element.h"


class Squirtle : public Element {

public:
    int width = 30;
    int height = 30;

    SDL_Point fposition;
    Unit* curunit;
    Texture* ftexture;
    SDL_Rect collider;

    Squirtle(Unit* Unitx, Texture* texture);

    void SetUnit(Unit* unitt);

    void Render();

    SDL_Rect GetCollider();

    void Remove();

    Unit* GetCurUnit();

    SDL_Point GetPos();

};
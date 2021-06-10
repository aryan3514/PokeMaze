#pragma once
#include "Texture.h"
#include "Unit.h"
#include "Matrix.h"
#include "Element.h"


class Gastly:  public Element {

public:
    int width = 20;
    int height = 20;

    SDL_Point fposition;
    Unit* curunit;
    Texture* ftexture;
    SDL_Rect collider;

    Gastly(Unit* Unitx, Texture* texture);

    void SetUnit(Unit* unitt);

    void Render();

    void Remove();

    SDL_Rect GetCollider();

    Unit* GetCurUnit();

    SDL_Point GetPos();

};
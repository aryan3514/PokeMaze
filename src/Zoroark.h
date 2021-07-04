#pragma once
#include "Texture.h"
#include "Unit.h"
#include "Matrix.h"
#include "Element.h"


class Zoroark : public Element {

public:
    int width = 30;
    int height = 30;

    SDL_Point fposition;
    Unit* curunit;
    Texture* ftexture;
    SDL_Rect collider;

    Zoroark(Unit* Unitx, Texture* texture);

    void SetUnit(Unit* unitt);

    void Remove();

    void Render();

    SDL_Rect GetCollider();

    Unit* GetCurUnit();

    SDL_Point GetPos();

};

#pragma once
#include "Texture.h"
#include "Unit.h"
#include "Matrix.h"
#include "Element.h"

class JigglyPuff : public Element {

    public:
    int width = 20;
    int height = 20;



    SDL_Point fposition;
    Unit* curunit;
    Texture* ftexture;

    SDL_Rect* collider;

    JigglyPuff (Unit* Unitx, Texture* texture);

    void Remove();

    SDL_Point GetPos();


    Unit* GetCurUnit();

    void Render();

    void SetUnit(Unit* unitt);

    SDL_Rect* GetCollider();


};
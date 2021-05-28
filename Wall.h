#include "Wall.h"
class Wall{

    int wwidth = 20;
    int wheight = 20;

    SDL_Point wposition;
    Box* curunit;
    Texture* walltexture;
    SDL_Rect collider;

    void SetUnit(Unit* unitt);

    void Render();

    SDL_Rect GetCollider();

    Unit GetCurUnit();

    SDL_Rect GetPos();

}
#include <SDL.h>

class Wall{

    int width = 20;
    int height = 20;

    SDL_Point position;
    Unit* curunit;
    Texture* walltexture;
    SDL_Rect collider;

    void SetUnit(Unit* unitt);

    void Render();

    SDL_Rect GetCollider();

    Unit GetCurUnit();

    SDL_Rect GetPos();

}
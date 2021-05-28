#include "Texture.h"
#include "Matrix.h"

class Pokeball{

    public:
    int fwidth = 20;
    int fheight = 20;

    SDL_Point fposition;
    Unit* curunit;
    Texture* ftexture;

    SDL_Rect* collider;

    Pokeball (Unit* Unitx, Texture* texture);

    void Render();

    void SetUnit(Unit* unitt);

    SDL_Rect GetCollider();

    Unit GetCurUnit();

    SDL_Rect GetPos();
};
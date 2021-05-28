#include <SDL.h>

class Ash;
class Wall;
class Pokeball;
class Monster;

class Unit{
    public :

    Ash* lAsh = NULL;
    Wall* lWall = NULL;
    Pokeball* lPokeball = NULL;
    Monster* lMonster = NULL;

    int width = 20;
    int height = 20;
    
    SDL_Point pos;

    Unit();

    Unit(int a, int b);

    void SetPos(int a, int b);

    void SetAsh (Ash Ashh);

    void SetPokeball (Pokeball ball);

    void SetWall (Wall wol);

    void SetMonster (Monster monsty);

    SDL_Point GetPos();

    Ash GetAsh();

    Wall GetWall();

    Pokeball GetPokeball();

    Monster GetMonster();

};
#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>


class Ash;
class Wall;
class Pokeball;
class Monster;
class Squirtle;
class JigglyPuff;
class Gastly;
class Zoroark;

class Unit{
    public :

    Ash* lAsh = NULL;
    Wall* lWall = NULL;
    Pokeball* lPokeball = NULL;
    Monster* lMonster = NULL;
    Squirtle* lSquirtle = NULL;
    JigglyPuff* lJigglyPuff = NULL;
    Gastly* lGastly = NULL;
    Zoroark* lZoroark = NULL;

    const static int width = 30;
    const static int height = 30;
    
    SDL_Point pos;

    Unit();

    Unit(int a, int b);

    void SetPos(int a, int b);

    void SetAsh (Ash* Ashh);

    void SetPokeball (Pokeball* ball);

    void SetWall (Wall* wol);

    void SetMonster (Monster* monsty);

    void SetSquirtle (Squirtle* squirtle);

    void SetJigglyPuff (JigglyPuff* jigg);

    void SetGastly (Gastly* gastly);

    void SetZoroark (Zoroark* zoroark);

    SDL_Point GetPos();

    Ash* GetAsh();

    Wall* GetWall();

    Pokeball* GetPokeball();

    Monster* GetMonster();

    Squirtle* GetSquirtle();

    JigglyPuff* GetJigglyPuff();

    Gastly* GetGastly();

    Zoroark* GetZoroark();

};

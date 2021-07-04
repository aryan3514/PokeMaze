#pragma once
#define SDL_MAIN_HANDLED
#include "Ash.h"
#include <SDL.h>
#include "Unit.h"
#include "Texture.h"
#include "Matrix.h"
#include "Element.h"
#include "Pokeball.h"
#include "Squirtle.h"
#include "JigglyPuff.h"
#include "Zoroark.h"
#include "Gastly.h"
#include "Wall.h"
#include <queue>
using namespace std;

class Monster : public Element {
public:



    static int points;

    bool squrtle = false;

    bool jpuff = false;

    bool gastly = false;

    bool zoroark = false;

    int speed = 1;


    int ash_width = 20;
    int ash_height = 20;

    int animcount = 4;

    bool pause = false;

    bool invincible = false;

    bool confusion = false;

    int frame_num = 0;

    SDL_Point position;
    Unit* curunit;
    Unit* nextunit;
    Texture* p_texture;
    SDL_Rect collider;
    Direction curdir;
    Direction nextdir;

    SDL_Rect UP_frames[2];
    SDL_Rect DOWN_frames[2];
    SDL_Rect LEFT_frames[2];
    SDL_Rect RIGHT_frames[2];

    void SetDimensions();

    bool isMoving = false;

    Monster(Unit* unitt, Texture* texture);

    void SetUnit(Unit* unitt);

    void Refresh();

    void Render();

    vector<Unit*> Byakugan(Unit* start, Unit* goal);

    bool CheckCollision(SDL_Rect other_collider);

    bool CheckCollisionForTwo(SDL_Rect first_collider, SDL_Rect second_collider);

    void HandleKeys(SDL_Event* event);

    bool MoveOneUnit(Direction dir);

    void ViewRefresh();

    bool isMonster();

    bool Motion();

    void PauseMonster();

    void ResumeMonster();

    void TurnMonsterPowerless();

    void ConfuseMonster();

    void TurnMonsterPowerful();

    void RemoveConfusion();

    Monster* GetMonsterFromElements();

    SDL_Rect GetCollider();

    Direction GetDirection();

    Direction GetNextDirection();

    Unit* GetCurUnit();

    Unit* GetNextUnit();

    SDL_Point GetPos();

    template <typename A, typename B>
    struct Cospair
    {
        Unit* unitt;
        float f;

        Cospair(Unit* uni, float val)
        {
            unitt = uni;
            f = val;
        }

        bool operator<(const struct Cospair& other) const
        {
            return f > other.f;
        }
    };

    ;
};

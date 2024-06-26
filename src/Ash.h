#pragma once
#define SDL_MAIN_HANDLED
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
#include <SDL_mixer.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STILL
};

class Ash : public Element {
public:

    Mix_Chunk* SquirtleSound = NULL;
    Mix_Chunk* JigglyPuffSound = NULL;
    Mix_Chunk* GastlySound = NULL;
    Mix_Chunk* ZoroarkSound = NULL;
    
    static int points;

    bool squrtle = false;

    bool jpuff = false;

    bool gastly  = false;

    bool zoroark = false;

    int speed = 3;


    int ash_width = 30;
    int ash_height = 30;

    
    int animcount = 4;



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

    Ash(Unit* unitt, Texture* texture);

    bool LoadSound();

    void SetUnit(Unit* unitt);

    void Refresh();

    void Remove();

    void Render();

    bool CheckCollision(SDL_Rect other_collider);
    
    bool CheckCollisionForTwo(SDL_Rect first_collider, SDL_Rect second_collider);

    void HandleKeys(SDL_Event* event);

    bool MoveOneUnit(Direction dir);

    bool Motion();

    bool isAsh();

    void ViewRefresh();

    SDL_Rect GetCollider();

    Direction GetDirection();

    Direction GetNextDirection();

    Unit* GetCurUnit();

    Unit* GetNextUnit();

    SDL_Point GetPos();

};
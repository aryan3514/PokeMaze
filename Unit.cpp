#include "Unit.h"

    Unit::Unit(int a, int b){
        pos = {a,b};
    }

    void Unit::SetPos(int a, int b){
        pos.x = a;
        pos.y = b;
    }

    void Unit::SetAsh (Ash Ashh){
        lAsh = Ashh;
    }

    void Unit::SetPokeball (Pokeball ball){
        lPokeball =  ball;
    }

    void Unit::SetWall (Wall wol){
        lWall = wol;
    }

    void Unit::SetMonster (Monster monsty){
        lMonster = monsty ;
    }

    SDL_Point Unit::GetPos(){
        return pos;
    }

    Ash Unit::GetAsh(){
        return lAsh;
    }


    Wall Unit::GetWall(){
        return lWall;
    }

    Pokeball Unit::GetPokeball(){
        return lPokeball;
    }

    Ash Unit::GetMonster(){
        return lMonster;
    }
#include "Unit.h"

    Unit::Unit() {
        pos = { 0,0 };
    }

    Unit::Unit(int a, int b){
        pos = {a,b};
    }

    void Unit::SetPos(int a, int b){
        pos.x = a;
        pos.y = b;
    }

    void Unit::SetAsh (Ash* Ashh){
        lAsh = Ashh;
    }

    void Unit::SetPokeball (Pokeball* ball){
        lPokeball =  ball;
    }

    void Unit::SetWall (Wall* wol){
        lWall = wol;
    }

    void Unit::SetMonster (Monster* monsty){
        lMonster = monsty ;
    }

    void Unit::SetSquirtle (Squirtle* squirtle){
        lSquirtle = squirtle;
    }

    void Unit::SetJigglyPuff (JigglyPuff* jigg){
        lJigglyPuff = jigg;
    }

    void Unit::SetGastly (Gastly* gastly){
        lGastly = gastly;
    }

    void Unit::SetZoroark (Zoroark* zoroark){
        lZoroark = zoroark;
    }

    SDL_Point Unit::GetPos(){
        return pos;
    }

    Ash* Unit::GetAsh(){
        return lAsh;
    }


    Wall* Unit::GetWall(){
        return lWall;
    }

    Pokeball* Unit::GetPokeball(){
        return lPokeball;
    }

    Monster* Unit::GetMonster(){
        return lMonster;
    }

    Squirtle* Unit::GetSquirtle (){
        return lSquirtle;
    }

    JigglyPuff* Unit::GetJigglyPuff(){
        return lJigglyPuff;
    }

    Gastly* Unit::GetGastly (){
        return lGastly;
    }

    Zoroark* Unit::GetZoroark (){
        return lZoroark;
    }
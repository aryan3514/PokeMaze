#include "Squirtle.h"

Squirtle::Squirtle (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    ftexture = texture;

    if (Unitx!=NULL){
        fposition.x = Unitx->GetPos.x*fwidth;
        fposition.y = Unitx->GetPos.x*fheight;
    }else{
        fposition.x = 0;
        fposition.y = 0;
    }

}

void Squirtle::Render(){
    ftexture->Render(fposition.x, fposition.y);
}

SDL_Point Squirtle::GetPos(){
    return fposition;
}

SDL_Rect Squirtle::GetCollider(){
    return collider;
}

Unit Squirtle::GetCurUnit(){
    return curunit;
}

SDL_Rect Squirtle::GetPos(){
    return fposition;
}


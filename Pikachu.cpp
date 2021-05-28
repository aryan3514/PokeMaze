#include "Wall.h"

Pikachu::Pikachu (Unit* Unitx, Texture* texture){

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

void Pikachu::Render(){
    ftexture->Render(fposition.x, fposition.y);
}

SDL_Point Pikachu::GetPos(){
    return fposition;
}


SDL_Rect Pikachu::GetCollider(){
    return collider;
}

Unit Pikachu::GetCurUnit(){
    return curunit;
}

SDL_Rect Pikachu::GetPos(){
    return fposition;
}

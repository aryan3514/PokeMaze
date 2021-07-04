#pragma once
#include "Gastly.h"
#include "Wall.h"

Gastly::Gastly (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    ftexture = texture;

    if (Unitx!=NULL){

        curunit->SetGastly(this);
        fposition.x = Unitx->GetPos().x*width + width_offset;
        fposition.y = Unitx->GetPos().y*height + height_offset;
    }else{
        fposition.x = width_offset;
        fposition.y = height_offset;
    }

    collider.w = width;
    collider.h = height;

    collider.x = fposition.x;
    collider.y = fposition.y;

}

void Gastly::Render(){
    ftexture->Render(fposition.x, fposition.y,0,SDL_FLIP_NONE);
}

SDL_Point Gastly::GetPos(){
    return fposition;
}

void Gastly::Remove() {
    Element::Remove();
    curunit->SetGastly(NULL);
}


SDL_Rect Gastly::GetCollider(){
    return collider;
}

Unit* Gastly::GetCurUnit(){
    return curunit;
}


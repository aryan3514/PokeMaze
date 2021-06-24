#include "Zoroark.h"
#include "Wall.h"

Zoroark::Zoroark (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    ftexture = texture;

    if (Unitx!=NULL){

        curunit->SetZoroark(this);
        fposition.x = Unitx->GetPos().x*width + width_offset;
        fposition.y = Unitx->GetPos().y*height + height_offset;
    }else{
        fposition.x = 0;
        fposition.y = 0;
    }

}

void Zoroark::Render(){
    ftexture->Render(fposition.x, fposition.y,0, SDL_FLIP_NONE);
}

SDL_Point Zoroark::GetPos(){
    return fposition;
}


SDL_Rect Zoroark::GetCollider(){
    return collider;
}

void Zoroark::Remove() {
    Element::Remove();
    curunit->SetZoroark(NULL);
}

Unit* Zoroark::GetCurUnit(){
    return curunit;
}


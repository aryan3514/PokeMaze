#include "Squirtle.h"

Squirtle::Squirtle (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    ftexture = texture;

    collider.w = width;
    collider.h = height;

    if (Unitx!=NULL){
        curunit->SetSquirtle(this);
        fposition.x = Unitx->GetPos().x*width + width_offset;
        fposition.y = Unitx->GetPos().y*height + height_offset;
    }else{
        fposition.x = 0;
        fposition.y = 0;
    }

}

void Squirtle::SetUnit(Unit *unitt)
{

    curunit = unitt;

    if (curunit != NULL)
    {
        curunit->SetSquirtle(this);

        fposition.x = curunit->GetPos().x * Unit::width + width_offset;
        fposition.y = curunit->GetPos().y * Unit::height + height_offset;
    }
}


void Squirtle::Render(){
    ftexture->Render(fposition.x, fposition.y,0, SDL_FLIP_NONE);
}

void Squirtle::Remove() {
    Element::Remove();
    curunit->SetSquirtle(NULL);
}

SDL_Point Squirtle::GetPos(){
    return fposition;
}

SDL_Rect Squirtle::GetCollider(){
    return collider;
}

Unit* Squirtle::GetCurUnit(){
    return curunit;
}



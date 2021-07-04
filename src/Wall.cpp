#include "Wall.h"

Wall::Wall (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    walltexture = texture;

    if (Unitx!=NULL){

        curunit->SetWall(this);
        position.x = Unitx->GetPos().x*width + width_offset;
        position.y = Unitx->GetPos().y*height + height_offset;
    }else{
        position.x = 0;
        position.y = 0;
    }

}

void Wall::SetUnit(Unit* unitt){

    curunit = unitt;

    if (curunit!=NULL){
        curunit->SetWall(this);

        position.x = curunit->GetPos().x * Unit::width + width_offset;
        position.y = curunit->GetPos().y * Unit::height + height_offset;
    }
}

void Wall::Render()
{
	walltexture->Render(position.x, position.y,0, SDL_FLIP_NONE);
}

SDL_Rect Wall::GetCollider(){
    return collider;
}

Unit* Wall::GetCurUnit(){
    return curunit;
}

SDL_Point Wall::GetPos(){
    return position;
}




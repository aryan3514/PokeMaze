#include "Wall.h"

Wall::Wall (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    walltexture = texture;

    if (Unitx!=NULL){
        position.x = Unitx->GetPos().x*width;
        position.y = Unitx->GetPos().y*height;
    }else{
        position.x = 0;
        position.y = 0;
    }

}

void Wall::SetUnit(Unit* unitt){

    curunit = unitt;

    if (curunit!=NULL){
        curunit->SetWall(this);

        position.x = curunit->GetPos().x * Unit::width;
        position.y = curunit->GetPos().y * Unit::height;
    }
}

void Wall::Render()
{
	walltexture->Render(position.x, position.y);
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




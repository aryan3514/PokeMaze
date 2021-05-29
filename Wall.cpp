#include "Wall.h"

Wall::Wall (Unit* Unitx, Texture* texture){

    curunit = Unitx;
    walltexture = texture;

    if (Unitx!=NULL){
        wposition.x = Unitx->GetPos.x*width;
        wposition.y = Unitx->GetPos.x*height;
    }else{
        wposition.x = 0;
        wposition.y = 0;
    }

}

void Wall::SetUnit(Unit* unitt){

    curunit = unit;

    if (curunit!=NULL){
        curunit.SetWall(this);

        wposition.x = curunit.GetPos().x * Unit::width;
        wposition.y = curunit.GetPos().y * Unit::height;
    }
}

void Wall::Render()
{
	wallTexture->Render(wposition.x, wposition.y);
}

SDL_Rect Wall::GetCollider(){
    return collider;
}

Unit Wall::GetCurUnit(){
    return curunit;
}

SDL_Rect Wall::GetPos(){
    return wposition;
}




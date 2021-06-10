#include "JigglyPuff.h"

JigglyPuff::JigglyPuff(Unit* Unitx, Texture* texture) {

    curunit = Unitx;
    ftexture = texture;


    if (Unitx != NULL) {
        curunit->SetJigglyPuff(this);
        fposition.x = Unitx->GetPos().x * width + width_offset;
        fposition.y = Unitx->GetPos().y * height + height_offset;
    }
    else {
        fposition.x = 0;
        fposition.y = 0;
    }

}

void JigglyPuff::SetUnit(Unit* unitt)
{

    curunit = unitt;

    if (curunit != NULL)
    {
        curunit->SetJigglyPuff(this);

        fposition.x = curunit->GetPos().x * Unit::width + width_offset;
        fposition.y = curunit->GetPos().y * Unit::height + height_offset;
    }
}


void JigglyPuff::Render() {
    ftexture->Render(fposition.x, fposition.y);
}

void JigglyPuff::Remove() {
    Element::Remove();
    curunit->SetSquirtle(NULL);
}

SDL_Point JigglyPuff::GetPos() {
    return fposition;
}

SDL_Rect* JigglyPuff::GetCollider() {
    return collider;
}

Unit* JigglyPuff::GetCurUnit() {
    return curunit;
}



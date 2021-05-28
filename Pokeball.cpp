#include "Pokeball.h"

Pokeball::Pokeball(Unit *Unitx, Texture *texture)
{

    curunit = Unitx;
    ftexture = texture;

    if (Unitx != NULL)
    {
        fposition.x = Unitx->GetPos.x * fwidth;
        fposition.y = Unitx->GetPos.x * fheight;
    }
    else
    {
        fposition.x = 0;
        fposition.y = 0;
    }
}

void Pokeball::SetUnit(Unit *unitt)
{

    curunit = unit;

    if (curunit != NULL)
    {
        curunit.SetPokeball(this);

        fposition.x = curunit.GetPos().x * Unit::width;
        fposition.y = curunit.GetPos().y * Unit::height;
    }
}

SDL_Rect Pokeball::GetCollider()
{
    return collider;
}

Unit Pokeball::GetCurUnit()
{
    return curunit;
}

void Pokeball::Render()
{
    ftexture->Render(fposition.x, fposition.y);
}

SDL_Point Pokeball::GetPos()
{
    return fposition;
}
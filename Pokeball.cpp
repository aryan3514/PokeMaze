
#include "Pokeball.h"

Pokeball::Pokeball(Unit *Unitx, Texture *texture)
{

    curunit = Unitx;
    ftexture = texture;

    if (Unitx != NULL)
    {
        position.x = Unitx->GetPos().x * width ;
        position.y = Unitx->GetPos().y* height ;
    }
    else
    {
        position.x = 0;
        position.y = 0;
    }

    collider.w = width;
	collider.h = height;

	collider.x = position.x;
	collider.y = position.y;
}

void Pokeball::SetUnit(Unit *unitt)
{

    curunit = unitt;

    if (curunit != NULL)
    {
        curunit->SetPokeball(this);

        position.x = curunit->GetPos().x * Unit::width;
        position.y = curunit->GetPos().y * Unit::height;
    }
}

SDL_Rect Pokeball::GetCollider()
{
    return collider;
}

Unit* Pokeball::GetCurUnit()
{
    return curunit;
}

void Pokeball::Render()
{
    ftexture->Render(position.x, position.y);
}

SDL_Point Pokeball::GetPos()
{
    return position;
}
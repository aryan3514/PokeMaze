
#include "Pokeball.h"

Pokeball::Pokeball(Unit *Unitx, Texture *texture)
{

    curunit = Unitx;
    ftexture = texture;

    if (Unitx != NULL)
    {
        curunit->SetPokeball(this);
        position.x = Unitx->GetPos().x * width + width_offset;
        position.y = Unitx->GetPos().y* height + height_offset;
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

        position.x = curunit->GetPos().x * Unit::width + width_offset;
        position.y = curunit->GetPos().y * Unit::height + height_offset;
    }
}

SDL_Rect Pokeball::GetCollider()
{
    return collider;
}

void Pokeball::Remove() {
    Element::Remove();
    curunit->SetPokeball(NULL);
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
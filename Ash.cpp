#include "Ash.h"
#include "Wall.h"

Ash::Ash(Unit *Unitx, Texture *texture)
{

    curunit = Unitx;
    p_texture = texture;

    if (Unitx != NULL)
    {
        position.x = Unitx->GetPos().x * ash_width;
        position.y = Unitx->GetPos().y * ash_height;
    }
    else
    {
        position.x = 0;
        position.y = 0;
    }

    curdir = RIGHT;
    nextdir = RIGHT;
}

void Ash::HandleKeys(SDL_Event *event)
{

    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (event.key.keysys.sym == SDLK_UP)
        {
            nextdir = UP;
        }
        else if (event.key.keysys.sym == SDLK_DOWN)
        {
            nextdir = DOWN;
        }
        else if (event.key.keysys.sym == SDLK_LEFT)
        {
            nextdir = LEFT;
        }
        else if (event.key.keysys.sym == SDLK_RIGHT)
        {
            nextdir = RIGHT;
        }
    }
}

bool Ash::MoveOneUnit(direction dir)
{
    if (dir == UP)
    {
        if (currUnit.GetPos().y - 1 < 0)
        {
            return false;
        }
        nextunit = Matrix::Area[currUnit.GetPos().x][currUnit.GetPos().y - 1];
    }
    else if (dir == DOWN)
    {
        if (currUnit.GetPos().y + 1 >= Matrix::height)
        {
            return false;
        }
        nextunit = Matrix::Area[currUnit.GetPos().x][currUnit.GetPos().y + 1];
    }
    else if (dir == LEFT)
    {
        if (currUnit.GetPos().x - 1 < 0)
        {
            return false;
        }
        nextunit = Matrix::Area[currUnit.GetPos().x - 1][currUnit.GetPos().y];
    }
    else if (dir == RIGHT)
    {
        if (currUnit.GetPos().x + 1 >= Matrix::width)
        {
            return false;
        }
        nextunit = Matrix::Area[currUnit.GetPos().x + 1][currUnit.GetPos().y];
    }

    return true;
}

void Ash::Render()
{

}

SDL_Point Ash::GetPos()
{
    return position;
}

SDL_Rect Ash::GetCollider(){
    return collider;
}

Direction Ash::GetDirection(){
    return curdir;
}

Direction Ash::GetNextDirection(){
    return nextdir;
}

Unit Ash::GetCurUnit(){
    return curunit;
}

Unit Ash::GetNextUnit(){
    return nextunit;
}

SDL_Rect GetPos(){
    return position;
}
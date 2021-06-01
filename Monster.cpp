#include "Monster.h"
#include "Wall.h"

/*Monster::Monster(Unit *Unitx, Texture *texture)
{

    curunit = Unitx;
    b_texture = texture;

    if (Unitx != NULL)
    {
        position.x = Unitx->GetPos().x * monster_width;
        position.y = Unitx->GetPos().y * monster_height;
    }
    else
    {
        position.x = 0;
        position.y = 0;
    }

    curdir = RIGHT;
    nextdir = RIGHT;
}

void Monster::HandleKeys(SDL_Event *event)
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

bool Monster::MoveOneUnit(direction dir)
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

void Monster::Render()
{


}

SDL_Point Monster::GetPos()
{
    return position;
}

SDL_Rect Monster::GetCollider(){
    return collider;
}

Direction Monster::GetDirection(){
    return curdir;
}

Direction Monster::GetNextDirection(){
    return nextdir;
}

Unit Monster::GetCurUnit(){
    return curunit;
}

Unit Monster::GetNextUnit(){
    return nextunit;
}

SDL_Rect Monster::GetPos(){
    return position;
}*/
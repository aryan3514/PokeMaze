#pragma once
#include "Monster.h"
#include "Wall.h"
#include "Matrix.h"
#include <string>
#include "Ash.h"
#include <cmath>
#include <algorithm>
#include <algorithm>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
using namespace std;



int Monster::points = 0;




Monster::Monster(Unit* unitt, Texture* texture)
{

    curunit = unitt;
    nextunit = NULL;
    p_texture = texture;

    collider.w = ash_width;
    collider.h = ash_height;

    if (unitt != NULL)
    {
        curunit->SetMonster(this);
        position.x = unitt->GetPos().x * ash_width + width_offset;
        position.y = unitt->GetPos().y * ash_height + height_offset;
    }
    else
    {
        position.x = width_offset;
        position.y = height_offset;
    }

    curdir = RIGHT;
    nextdir = RIGHT;
}

void Monster::HandleKeys(SDL_Event* event)
{

    /*if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_w)
        {
            nextdir = UP;
        }
        else if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s)
        {
            nextdir = DOWN;
        }
        else if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_a)
        {
            nextdir = LEFT;
        }
        else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d)
        {
            nextdir = RIGHT;
        }
    }*/
}

bool Monster::MoveOneUnit(Direction dir)
{
    if (dir == UP)
    {
        if (curunit->GetPos().y - 1 < 0)
        {
            return false;
        }
        nextunit = Element_Matrix->GetUnitFromMatrix(curunit->GetPos().x, curunit->GetPos().y - 1);

    }
    else if (dir == DOWN)
    {
        if (curunit->GetPos().y + 1 >= Element_Matrix->height)
        {
            return false;
        }
        nextunit = Element_Matrix->GetUnitFromMatrix(curunit->GetPos().x, curunit->GetPos().y + 1);
    }
    else if (dir == LEFT)
    {
        if (curunit->GetPos().x - 1 < 0)
        {
            return false;
        }
        nextunit = Element_Matrix->GetUnitFromMatrix(curunit->GetPos().x - 1, curunit->GetPos().y);
    }
    else if (dir == RIGHT)
    {
        if (curunit->GetPos().x + 1 >= Element_Matrix->width)
        {
            return false;
        }
        nextunit = Element_Matrix->GetUnitFromMatrix(curunit->GetPos().x + 1, curunit->GetPos().y);
    }

    if (nextunit == NULL || nextunit->GetWall() != NULL) {
        nextunit = NULL;
        return false;
    }

    return true;
}

void Monster::Render()
{
    p_texture->Render(position.x, position.y,0, SDL_FLIP_NONE);
    /*if (curdir==UP){
        p_texture->Render(position.x, position.y, &UP_frames[frame_num]);
    }
    else if(curdir==DOWN){
        p_texture->Render(position.x, position.y, &DOWN_frames[frame_num]);
    }
    else if(curdir==LEFT){
        p_texture->Render(position.x, position.y, &LEFT_frames[frame_num]);
    }
    else if(curdir==LEFT){
        p_texture->Render(position.x, position.y, &RIGHT_frames[frame_num]);
    }*/

}


vector<Unit*> Monster::Byakugan(Unit* start, Unit* goal) {
    map<Unit*, Unit*> old_path;
    map<Unit*, float> cost;

    old_path[start] = start;
    cost[start] = 0;

    priority_queue<Cospair<Unit*, float>> PriorityUnit;
    

    PriorityUnit.emplace(Cospair<Unit*, float>(start, 0));
    vector<Unit*> path;
    
    while (!PriorityUnit.empty()) {
        
        Unit* curr = PriorityUnit.top().unitt;
        PriorityUnit.pop();

        if (curr == goal) {
            break;
        }

        
        vector<Unit*> neburs = Element_Matrix->GetNeighbours(curr);


        for (int i = 0; i < neburs.size(); i++) {
            float ncost = cost[curr] + 1;

            if (neburs[i] != NULL && (!cost.count(neburs[i]) || ncost < cost[neburs[i]])){

                if (neburs[i]->GetWall()!=NULL|| neburs[i]->GetMonster()!=NULL) ncost = INFINITY;

                cost[neburs[i]] = ncost;

                PriorityUnit.emplace(Cospair<Unit*, float>(neburs[i], ncost + abs(goal->GetPos().x - neburs[i]->GetPos().x) + abs(goal->GetPos().y - neburs[i]->GetPos().y)));
                old_path[neburs[i]] = curr;
            }

        }
    }

    

    
    Unit* current = goal;

    path.push_back(current);

    while (current != start) {
        current = old_path[current];
        path.push_back(current);
    }

    reverse(path.begin(), path.end());

    return path;

}


void Monster::PauseMonster() {
    pause = true;
}

void Monster::ResumeMonster() {
    pause = false;
}

void Monster::TurnMonsterPowerless() {
    invincible = true;
}

void Monster::TurnMonsterPowerful() {
    invincible = false;
}

void Monster::ConfuseMonster() {
    confusion = true;
}

void Monster::RemoveConfusion() {
    confusion = false;
}

Monster* Monster::GetMonsterFromElements(){
    return curunit->GetMonster();
}

void Monster::Refresh() {

    srand(time(0));
    
    Ash* Ashboy = Element_Matrix->FindAsh();


    if (Ashboy != NULL) {

        if (curunit == nextunit || nextunit==NULL) {
            
            if (Ashboy == NULL) {
                return;
            }

            vector<Unit*>  finpath;

            if (confusion) {


                int a = rand() % (Element_Matrix->width);
                int b = rand() % (Element_Matrix->height);

                while (Element_Matrix->GetUnitFromMatrix(a, b)!=NULL && Element_Matrix->GetUnitFromMatrix(a, b)->GetMonster()!=NULL) {

                    a = rand() % (Element_Matrix->width);
                    b = rand() % (Element_Matrix->height);
                }
                finpath = Byakugan(curunit, Element_Matrix->GetUnitFromMatrix(a, b));
            }
            else {
                finpath = Byakugan(curunit, Ashboy->GetCurUnit());
            }
            

            if (finpath.size() < 2) {
                return;
            }

            

            if (pause) {
                nextunit = curunit;
            }
            else {
                nextunit = finpath[1];
            }

            

            if (position.x < nextunit->GetPos().x * Unit::width + width_offset) {
                curdir = RIGHT;
            }
            else if (position.x > nextunit->GetPos().x * Unit::width + width_offset) {
                curdir = LEFT;
            }
            else if (position.y < nextunit->GetPos().y * Unit::height + height_offset) {
                curdir = DOWN;
            }
            else if (position.y > nextunit->GetPos().y * Unit::height + height_offset) {
                curdir = UP;
            }

            if (curunit->GetAsh() != NULL && !invincible) {
                curunit->GetAsh()->Remove();
                return;
            }

            for (auto i : Element_Matrix->GetNeighbours(curunit)) {
                if (i->GetAsh() != NULL && !invincible) {
                    i->GetAsh()->Remove();
                    //exit(0);
                    return;
                }


            }
        }

        if (!confusion) {

            if (curdir == UP) {
                position.y = max(position.y - speed, nextunit->GetPos().y * Unit::height + height_offset);
            }
            else if (curdir == DOWN) {
                position.y = min(position.y + speed, nextunit->GetPos().y * Unit::height + height_offset);
            }
            else if (curdir == LEFT) {
                position.x = max(position.x - speed, nextunit->GetPos().x * Unit::width + width_offset);
            }
            else if (curdir == RIGHT) {
                position.x = min(position.x + speed, nextunit->GetPos().x * Unit::width + width_offset);
            }

        }
        else {
            if (curdir == UP) {
                position.y = max(position.y - speed, nextunit->GetPos().y * Unit::height + height_offset);
            }
            else if (curdir == DOWN) {
                position.y = min(position.y + speed, nextunit->GetPos().y * Unit::height + height_offset);
            }
            else if (curdir == LEFT) {
                position.x = max(position.x - speed, nextunit->GetPos().x * Unit::width + width_offset);
            }
            else if (curdir == RIGHT) {
                position.x = min(position.x + speed, nextunit->GetPos().x * Unit::width + width_offset);
            }
        }
        

        if ((curdir == LEFT || curdir == RIGHT) && position.x == nextunit->GetPos().x * Unit::width + width_offset) {
            if (nextunit->GetMonster() != NULL) {
                position.x == curunit->GetPos().x * Unit::width + width_offset;
                SetUnit(curunit);
            }
            else {
                SetUnit(nextunit);
            }
        }

        if ((curdir == UP || curdir == DOWN) && position.y == nextunit->GetPos().y * Unit::height + height_offset) {
            if (nextunit->GetMonster() != NULL) {
                position.y == curunit->GetPos().y * Unit::height + height_offset;
                SetUnit(curunit);
            }
            else {
                SetUnit(nextunit);
            }
        }

    }

}

bool Monster::isMonster() {
    return false;
}
void Monster::ViewRefresh() {

    double unx = (double) (position.x - width_offset) / (double)Unit::width;;
    double uny = (double)(position.y - height_offset) / (double) Unit::height;;

    if (floor(unx) == unx && floor(uny) == uny) {
        SetUnit(Element_Matrix->GetUnitFromMatrix(unx,uny));
    }
   
    
}

void Monster::SetDimensions() {
    UP_frames[0] = {}; //set dimensions in the image 
    UP_frames[1] = {}; //set dimensions in the image 

    DOWN_frames[0] = {}; //set dimensions in the image 
    DOWN_frames[1] = {}; //set dimensions in the image 

    LEFT_frames[0] = {}; //set dimensions in the image 
    LEFT_frames[1] = {}; //set dimensions in the image 

    RIGHT_frames[0] = {}; //set dimensions in the image 
    RIGHT_frames[1] = {}; //set dimensions in the image
}

void Monster::SetUnit(Unit* unitt) {

    if (curunit != NULL) { curunit->SetMonster(NULL); }
    curunit = unitt;
    if (curunit != NULL) {
        curunit->SetMonster(this);
        position.x = curunit->GetPos().x * Unit::width + width_offset;
        position.y = curunit->GetPos().y * Unit::height + height_offset;
    }
}

bool Monster::CheckCollision(SDL_Rect other_collider) {

    if (collider.x + collider.w < other_collider.x) {
        return false;
    }

    if (collider.y + collider.h < other_collider.y) {
        return false;
    }

    if (collider.x > other_collider.x + other_collider.w) {
        return false;
    }

    if (collider.y > other_collider.y + other_collider.h) {
        return false;
    }

    return true;

    //CHECK

    /*if (collider.x + collider.w > other_collider.x && collider.x < other_collider.x ){
        return true;
    }

    if (collider.y + collider.h > other_collider.y && collider.y < other_collider.y ){
        return true;
    }

    if (other_collider.x + other_collider.w  > collider.x && collider.x > other_collider.x ){
        return true;
    }

    if (other_collider.y + other_collider.h  > collider.y && collider.y > other_collider.y ){
        return true;
    }

    return false;*/
}
bool Monster::CheckCollisionForTwo(SDL_Rect first_collider, SDL_Rect second_collider) {

    if (first_collider.x + first_collider.w < second_collider.x) {
        return false;
    }

    if (first_collider.y + first_collider.h < second_collider.y) {
        return false;
    }

    if (first_collider.x > second_collider.x + second_collider.w) {
        return false;
    }

    if (first_collider.y > second_collider.y + second_collider.h) {
        return false;
    }

    return true;

}

bool Monster::Motion() {
    return isMoving;
}

SDL_Point Monster::GetPos()
{
    return position;
}

SDL_Rect Monster::GetCollider() {
    return collider;
}

Direction Monster::GetDirection() {
    return curdir;
}

Direction Monster::GetNextDirection() {
    return nextdir;
}

Unit* Monster::GetCurUnit() {
    return curunit;
}

Unit* Monster::GetNextUnit() {
    return nextunit;
}

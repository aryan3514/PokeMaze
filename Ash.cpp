#pragma once
#include "Ash.h"
#include "Wall.h"
#include "Matrix.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <stdio.h>
using namespace std;


int Ash::points = 0;

Ash::Ash(Unit* unitt, Texture* texture)
{

    curunit = unitt;
    nextunit = NULL;
    p_texture = texture;

    collider.w = ash_width;
    collider.h = ash_height;

    if (unitt != NULL)
    {
        curunit->SetAsh(this);
        position.x = unitt->GetPos().x * ash_width + width_offset;
        position.y = unitt->GetPos().y * ash_height +height_offset;
    }
    else
    {
        position.x = width_offset;
        position.y = height_offset;
    }

    LoadSound();

    curdir = RIGHT;
    nextdir = RIGHT;
}

void Ash::HandleKeys(SDL_Event *event)
{

    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
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
        else if (event->key.keysym.sym == SDLK_RIGHT|| event->key.keysym.sym == SDLK_d)
        {
            nextdir = RIGHT;
        }
    }
}

bool Ash::MoveOneUnit(Direction dir)
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


bool Ash::LoadSound()
{

    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    ankita = Mix_LoadWAV("ank.wav");
    SquirtleSound = Mix_LoadWAV("squirtle.wav");
    JigglyPuffSound = Mix_LoadWAV("jigglypuff.wav");
    GastlySound = Mix_LoadWAV("gastly.wav");
    ZoroarkSound = Mix_LoadWAV("zoroark.wav");

    if (SquirtleSound == NULL || JigglyPuffSound == NULL || GastlySound == NULL || ZoroarkSound == NULL) {
        return false;
    }

    return false;
}

void Ash::Render()
{
    
    if (curdir==UP){
        p_texture->Render(position.x, position.y, 270, SDL_FLIP_NONE);
    }
    else if(curdir==DOWN){
        p_texture->Render(position.x, position.y,90, SDL_FLIP_NONE);
    }
    else if(curdir==LEFT){
        p_texture->Render(position.x, position.y, 0.0, SDL_FLIP_HORIZONTAL);
    }
    else if(curdir==RIGHT){
        p_texture->Render(position.x, position.y, 0.0, SDL_FLIP_NONE);
    }

}

void Ash::Refresh(){

    //NOTE

    
    if (curunit!=NULL && curunit->GetPokeball()!=NULL){
        SDL_Rect arr = { position.x, position.y, ash_width, ash_height };
        // SUS about the Check Collision Method's need.
        //if (CheckCollisionForTwo(arr, curunit->GetPokeball()->GetCollider())){
            //DELETE THE POKEBALL; DELETE YET TO BE IMPLEMENTED
       //Mix_PlayChannel(-1, ankita, 0);
       
        curunit->GetPokeball()->Remove();
        points++;
       // }
    }

    if (curunit!=NULL && curunit->GetSquirtle()!=NULL){
        //if (CheckCollisionForTwo(SDL_Rect(position.x,position.y, ash_width, ash_height), nextunit->GetSquirtle()->GetCollider()){
            //DELETE THE POKEBALL; DELETE YET TO BE IMPLEMENTED
        Mix_PlayChannel(-1, SquirtleSound, 0);

        curunit->GetSquirtle()->Remove();
        squrtle = true;
        //}
    }

    if (curunit!=NULL && curunit->GetJigglyPuff()!=NULL){
        //if (CheckCollisionForTwo(SDL_Rect(position.x,position.y, ash_width, ash_height), nextunit->GetJigglyPuff()->GetCollider()){
            //DELETE THE POKEBALL; DELETE YET TO BE IMPLEMENTED
        Mix_PlayChannel(-1, JigglyPuffSound, 0);
        curunit->GetJigglyPuff()->Remove();
        jpuff = true;
        //}
    }

    if (curunit!=NULL && curunit->GetGastly()!=NULL){
        //if (CheckCollisionForTwo(SDL_Rect(position.x,position.y, ash_width, ash_height), nextunit->GetGastly()->GetCollider()){
            //DELETE THE POKEBALL; DELETE YET TO BE IMPLEMENTED
        Mix_PlayChannel(-1, GastlySound, 0);
        curunit->GetGastly()->Remove();
        gastly = true;
        //}
    }

    if (curunit!=NULL && curunit->GetZoroark()!=NULL){
        //if (CheckCollisionForTwo(SDL_Rect(position.x,position.y, ash_width, ash_height), nextunit->GetZoroark()->GetCollider()){
            //DELETE THE POKEBALL; DELETE YET TO BE IMPLEMENTED
            Mix_PlayChannel(-1, ZoroarkSound, 0);
            curunit->GetZoroark()->Remove();
            zoroark = true;
        //}
    }

    if (curunit==nextunit || nextunit==NULL){
        if (curdir!=nextdir){
            if (MoveOneUnit(nextdir)){
                curdir = nextdir;
            }else{
                MoveOneUnit(curdir);
            }
        }else{
            MoveOneUnit(curdir);
        }

        if (nextunit==NULL){
            isMoving = false;
        }else{
            isMoving = true;
        }
    }else{

        if (curdir == UP){
            position.y = max(position.y - speed , nextunit->GetPos().y*Unit::height + height_offset) ;
        }else if (curdir==DOWN){
            position.y = min(position.y + speed, nextunit->GetPos().y*Unit::height + height_offset);
        }else if (curdir==LEFT){
            position.x = max(position.x - speed, nextunit->GetPos().x*Unit::width + width_offset);
        }else if (curdir ==RIGHT){
            position.x = min(position.x + speed, nextunit->GetPos().x*Unit::width + width_offset);
        }

        if ((curdir==LEFT|| curdir == RIGHT) && position.x == nextunit->GetPos().x*Unit::width + width_offset){
            SetUnit(nextunit);
        }

        if ((curdir == UP|| curdir == DOWN) && position.y == nextunit->GetPos().y*Unit::height + height_offset){
            SetUnit(nextunit);
        }
        collider.x = position.x;
        collider.y = position.y;
    }

}

void Ash::SetDimensions() {
    UP_frames[0] = {}; //set dimensions in the image 
    UP_frames[1] = {}; //set dimensions in the image 

    DOWN_frames[0] = {}; //set dimensions in the image 
    DOWN_frames[1] = {}; //set dimensions in the image 

    LEFT_frames[0] = {}; //set dimensions in the image 
    LEFT_frames[1] = {}; //set dimensions in the image 

    RIGHT_frames[0] = {}; //set dimensions in the image 
    RIGHT_frames[1] = {}; //set dimensions in the image
}

void Ash::SetUnit(Unit* unitt){

    if (curunit != NULL) { curunit->SetAsh(NULL); }
    curunit = unitt;
    if (curunit!=NULL){
        curunit->SetAsh(this);
        position.x = curunit->GetPos().x*Unit::width + width_offset;
        position.y = curunit->GetPos().y*Unit::height + height_offset;
    }
}

bool Ash::CheckCollision(SDL_Rect other_collider){

    if (collider.x + collider.w < other_collider.x ){
        return false;
    }

    if (collider.y + collider.h < other_collider.y ){
        return false;
    }

    if (collider.x > other_collider.x + other_collider.w ){
        return false;
    }
    
    if (collider.y > other_collider.y + other_collider.h ){
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
bool Ash::CheckCollisionForTwo(SDL_Rect first_collider, SDL_Rect second_collider){

    if (first_collider.x + first_collider.w < second_collider.x ){
        return false;
    }

    if (first_collider.y + first_collider.h < second_collider.y ){
        return false;
    }

    if (first_collider.x > second_collider.x + second_collider.w ){
        return false;
    }
    
    if (first_collider.y > second_collider.y + second_collider.h ){
        return false;
    }

    return true;

}

void Ash::Remove(){
    Element::Remove();
    curunit->SetAsh(NULL);
}

bool Ash::Motion(){
    return isMoving;
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

Unit* Ash::GetCurUnit(){
    return curunit;
}

Unit* Ash::GetNextUnit(){
    return nextunit;
}

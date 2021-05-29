#include <SDL.h>
#include <Unit.h>



class Ash{

    enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STILL  
    };

    int ash_width = 50;
    int ash_height = 50;
    
    int animcount = 4;

    int frames = 2;

    SDL_Point position;
    Unit* curunit;
    Unit* nextunit;
    Texture* p_texture;
    SDL_Rect collider;
    Direction curdir;
    Direction nextdir;

    SDL_Rect UP_frames[frames];
    SDL_Rect DOWN_frames[frames];
    SDL_Rect LEFT_frames[frames];
    SDL_Rect RIGHT_frames[frames];

    UP_frames[0] = {}; //set dimensions in the image 
    UP_frames[1] = {}; //set dimensions in the image 

    DOWN_frames[0] = {}; //set dimensions in the image 
    DOWN_frames[1] = {}; //set dimensions in the image 

    LEFT_frames[0] = {}; //set dimensions in the image 
    LEFT_frames[1] = {}; //set dimensions in the image 

    RIGHT_frames[0] = {}; //set dimensions in the image 
    RIGHT_frames[1] = {}; //set dimensions in the image

    bool isMoving = false;

    Ash(Unit* unitt, Texture* texture);

    void SetUnit(Unit* unitt);

    void Refresh();

    bool CheckCollision(SDL_Rect other_collider);

    void HandleKeys(SDL_Event* event);

    bool MoveOneUnit(Direction dir);

    bool Motion();

    SDL_Rect GetCollider();

    Direction GetDirection();

    Direction GetNextDirection();

    Unit GetCurUnit();

    Unit GetNextUnit();

    SDL_Rect GetPos();

};
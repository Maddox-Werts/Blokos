// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "../gme/scene.h"
#include "../app/sound.h"
#include "../app/dtime.h"
#include "monster.h"

// Constants
#define FALLT 4
#define RESPAWNT 40
#define FALLSLICE 120.0f/1000.0f

// Variables
float ftime = 0;

// Functions
// --HELPER
void px_MACTIVATE(PX_Monster* monster){    

    // Adding to time
    if(ftime > RESPAWNT){
        ftime = 0;
        monster->active     = true;
        monster->x          = 3;
        monster->y          = 0;

        // Making the sounds
        px_SoundPlay("res/sounds/entities/monster_anger.wav", 2);
    }
    else{
        ftime += deltatime * FALLSLICE;
    }
}

void px_MFALL(PX_Monster* monster){
    if(ftime > FALLT){
        monster->y += 1;
        ftime = 0;
    }
    else{
        ftime += deltatime * FALLSLICE;
    }

    // Are we below the grid?
    if(monster->y > GRIDY){
        monster->active = false;
        return;
    }
}
void px_MSTRIDE(PX_Monster* monster){
    // Can we even move?
    if(ftime < FALLT){
        return;
    }

    // Getting a random direction
    srand(time(NULL));

    // Helpers
    int randec, direction;
    
    // Getting the random range
    randec = rand() % 100;
    
    // Here's whats gonna happen:
    /*
        IF: The range is between 0-40
        THEN: Move LEFT

        IF: the range is between 40-60
        THEN: Stay put
        
        IF: the range is between 60-100
        THEN: Move RIGHT
    */

    if(randec < 40){
        direction = -1;
    }
    else if(40 < randec && randec < 60){
        return;
    }
    else if(60 < randec && randec < 100){
        direction = +1;
    }
    else{
        printf("What did you do? It's broken?\n");
    }

    // Can we move in the direction we want?
    if(monster->x + direction < 0
    || monster->x + direction > GRIDX - 1){
        return;
    }

    monster->x += direction;

    // Sounds
    px_SoundPlay("res/sounds/entities/monster_jump.wav", 2);
}

// --HEADER
PX_Monster px_MonsterCreate(SDL_Renderer* renderer){
    // Holding
    PX_Monster monster;

    // Setting variables
    monster.active  = false;
    monster.x       = 3;
    monster.y       = 0;

    // Creating the texture
    monster_tex = px_TextureCreate(renderer, "res/sprites/monster.png");

    // Returning monster
    return monster;
}
void px_MonsterUpdate(PX_Monster* monster, PX_Scene* scene){

    // Active?
    if(!monster->active) {px_MACTIVATE(monster); return;}

    // Physics
    px_MSTRIDE(monster);
    px_MFALL(monster);
    
    // The fun stuff
}
void px_MosnterDraw(SDL_Renderer* renderer, PX_Scene* scene, PX_Monster* monster){
    // Active?
    if(!monster->active) {return;}

    // Making shapes
    SDL_Rect rect;

    // Constants
    const int _xgrid = scene->width     / GRIDX;
    const int _ygrid = scene->height    / GRIDY;

    // Updating positional values
    rect.x = monster->x * _xgrid;       rect.y = monster->y * _ygrid;
    rect.w = _xgrid;                    rect.h = _ygrid;

    // Set Color
    SDL_SetRenderDrawColor(renderer, 255,255,255, 1);
    SDL_RenderFillRect(renderer, &rect);

    // Drawing texture
    SDL_RenderCopy(renderer, monster_tex, NULL, &rect);
}
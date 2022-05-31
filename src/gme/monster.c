// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "../gme/scene.h"
#include "../app/dtime.h"
#include "monster.h"

// Constants
#define FALLT 4
#define FALLSLICE 120.0f/1000.0f

// Variables
float ftime = 0;

// Functions
// --HELPER
void px_MFALL(PX_Monster* monster){
    if(ftime > FALLT){
        monster->y += 1;
        ftime = 0;
    }
    else{
        ftime += deltatime * FALLSLICE;
    }
}

// --HEADER
PX_Monster px_MonsterCreate(){
    // Holding
    PX_Monster monster;

    // Setting variables
    monster.active  = true;
    monster.x       = 3;
    monster.y       = 0;

    // Returning monster
    return monster;
}
void px_MonsterUpdate(PX_Monster* monster){
    // Physics
    px_MFALL(monster);
}
void px_MosnterDraw(SDL_Renderer* renderer, PX_Scene* scene, PX_Monster* monster){
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
}
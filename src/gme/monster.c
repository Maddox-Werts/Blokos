// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "monster.h"

// Functions
PX_Monster px_MonsterCreate(){
    // Holding
    PX_Monster monster;

    // Setting variables
    monster.active  = true;
    monster.x       = 0;
    monster.y       = 0;

    // Returning monster
    return monster;
}
void px_MonsterUpdate(PX_Monster* monster){
    monster->y += 1;
}
void px_MosnterDraw(SDL_Renderer* renderer, PX_Monster* monster){
    // Making shapes
    SDL_Rect rect;

    // Updating positional values
    rect.x = monster->x;    rect.y = monster->y;
    rect.w = 50; rect.h = 50;

    // Set Color
    SDL_SetRenderDrawColor(renderer, 255,255,255, 1);
    SDL_RenderFillRect(renderer, &rect);
}
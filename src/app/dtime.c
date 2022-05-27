// Files
// --SYSTEM
#include <stdio.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "dtime.h"

// Functions
void updateTime(){
    // Time details
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    // Getting DT
    deltatime = (float)( (NOW - LAST) * 100 / (float)SDL_GetPerformanceFrequency() );
}
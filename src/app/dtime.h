// Define once
#ifndef H_DTIME
#define H_DTIME

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>

// Variables
Uint64 NOW, LAST;
float deltatime;

// Functions
void updateTime();

// End definition
#endif
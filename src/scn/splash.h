// Define once
#ifndef H_SPLASH
#define H_SPLASH

// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "../app/dtime.h"

// Variables
bool px_ssready;

// Functions
void px_SSstart(SDL_Renderer* renderer, int width, int height);
void px_SSupdate();
void px_SSdraw(SDL_Renderer* renderer, int width, int height);

// End definition
#endif
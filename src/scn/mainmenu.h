// Define once
#ifndef H_MAINMENU
#define H_MAINMENU

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "../app/text.h"

// CONSTANTS
// VARIABLES
SDL_Texture* titletex;
PX_Text start_txt;
bool px_mcanstart;

// Functions
void blk_MMCreate(SDL_Renderer* renderer);
void blk_MMUpdate();
void blk_MMDraw(SDL_Renderer* renderer);
void blk_MMClean();

// End definition
#endif
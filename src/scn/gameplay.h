// Define once
#ifndef H_GAMEPLAY
#define H_GAMEPLAY

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "../gme/scene.h"
#include "../gme/tetrimino.h"

// Scene Variables
PX_Tetrimino tetrimino;
PX_Scene scene;
bool didpress;

// Functions
void blk_GameStart();
void blk_GameUpdate();
void blk_GameDraw(SDL_Renderer* renderer);

// End definition
#endif
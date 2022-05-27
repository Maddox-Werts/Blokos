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
#include "../app/text.h"

// Scene Variables
PX_Tetrimino tetrimino;
PX_Scene scene;
bool didpress;

// Scene labels and stuff

// Functions
void blk_GameStart(SDL_Renderer* renderer);
void blk_GameUpdate();
void blk_GameDraw(SDL_Renderer* renderer);

// End definition
#endif
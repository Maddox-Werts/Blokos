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
#include "../gme/monster.h"

// Scene Variables
PX_Tetrimino tetrimino;
PX_Scene scene;
bool didpress;

// Texts
PX_Text score_txt;
PX_Text score_num_txt;

// Entities
PX_Monster monster;

// Functions
void blk_GameStart(SDL_Renderer* renderer);
void blk_GameUpdate();
void blk_GameDraw(SDL_Renderer* renderer);

// End definition
#endif
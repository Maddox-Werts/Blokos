// Define once
#ifndef H_TETRIMINO
#define H_TETRIMINO

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
// --HEADERS
#include "scene.h"
#include "../app/sound.h"

// Structures
typedef struct PX_Tetrimino{
    // Variables
    int x,y;
    int ox,oy;
    int type;

    // Cases
    bool still;

    // Timers
    float ft;
} PX_Tetrimino;

// Functions
PX_Tetrimino px_TetriminoCreate();
void px_TetriminoDelete(PX_Tetrimino* tetrimino);

void px_TetriminoUpdate(PX_Tetrimino* tetrimino, PX_Scene* scene);
void px_TetriminoDraw(PX_Tetrimino* tetrimino, PX_Scene* scene);
void px_TetriminoMove(PX_Tetrimino* tetrimino, PX_Scene* scene, int x, int y);
void px_TetriminoDrop(PX_Tetrimino* tetrimino, PX_Scene* scene);

// End definition
#endif
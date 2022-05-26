// Define once
#ifndef H_TETRIMINO
#define H_TETRIMINO

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "scene.h"
#include "tetrimino.h"

// Structures
struct PX_Tetrimino{
    // Variables
    int x,y;
    int type;

    // Cases
    bool still;

    // Timers
    float ft;
};

// Functions
struct PX_Tetrimino px_TetriminoCreate();
void px_TetriminoDelete(struct PX_Tetrimino* tetrimino);

void px_TetriminoUpdate(struct PX_Tetrimino* tetrimino);
void px_TetriminoDraw(struct PX_Tetrimino* tetrimino, struct PX_Scene* scene);
void px_TetriminoMove(struct PX_Tetrimino* tetrimino, int x, int y);

// End definition
#endif
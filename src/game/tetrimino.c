// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "tetrimino.h"

// CONSTANTS
#define FTIME 10.0f/1000.0f

// Functions
// --HELPERS
/*
    Helper Function Format:
    void px_T[FUNCTION NAME](struct PX_Tetrimino* tetrimino);

    Also no, I'm not going to use TYPEDEF for my structures.
    I do NOT know how to use those haha
*/
// ----PHYSICS
void px_TFALL(struct PX_Tetrimino* tetrimino){
    if(tetrimino->ft > 4){
        tetrimino->y += 1;
        tetrimino->ft = 0;
    }
    else{
        tetrimino->ft += FTIME;
    }
}
void px_TBORDER(struct PX_Tetrimino* tetrimino){
    if(tetrimino->y >= GRIDY - 2){
        tetrimino->still = true;
    }
}

// --REGULARS
struct PX_Tetrimino px_TetriminoCreate(){
    // Making stuff
    struct PX_Tetrimino tetrimino;

    // Assigning Variables
    tetrimino.x             = 3;
    tetrimino.y             = 0;
    tetrimino.ft            = 0;
    tetrimino.type          = 0;

    tetrimino.still         = false;

    // Giving back tetrimino
    return tetrimino;
}
void px_TetriminoDelete(struct PX_Tetrimino* tetrimino){
    free(tetrimino);
}

void px_TetriminoUpdate(struct PX_Tetrimino* tetrimino){
    // Are we static?
    if(tetrimino->still)    {return;}

    // Physics
    px_TFALL(tetrimino);

    // Checks
    px_TBORDER(tetrimino);
}
void px_TetriminoDraw(struct PX_Tetrimino* tetrimino, struct PX_Scene* scene){
    // Going through each type
    switch(tetrimino->type){
    // The I piece
    case 0:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_I[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;

    // The J piece
    case 1:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_J[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;

    // The L piece
    case 2:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_L[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;
    
    // The O piece
    case 3:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_O[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;

    // The S piece
    case 4:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_S[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;
    
    // The T piece
    case 5:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_T[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;
    
    // The Z piece
    case 6:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                if(te_Z[y*4+x] == 1){
                    px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y);
                }
            }
        }
        break;
    
    default:
        break;
    }
}
void px_TetriminoMove(struct PX_Tetrimino* tetrimino, int x, int y){
    // Moving the wanted tetrimino
    // Getting the width
    int width;

    // What's your type?
    switch(tetrimino->type){
    case 0:
        width = 4;      break;
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        width = 3;      break;
    case 3:
        width = 2;      break;
    }

    // Can we move?
    if((x < 0 && tetrimino->x + x + 1 > 0) || 
    (x > 0 && tetrimino->x + width + x - 1 < GRIDX)){           // Moving Left and Right but, WITH boundries.
        tetrimino->x += x;
    }
}

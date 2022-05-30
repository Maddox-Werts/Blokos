// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
// --HEADERS
#include "tetrimino.h"
#include "../app/sound.h"
#include "../app/dtime.h"

// CONSTANTS
#define FTIME 120.0f/1000.0f

// Functions
// --HELPERS
/*
    Helper Function Format:
    void px_T[FUNCTION NAME](PX_Tetrimino* tetrimino);

    Also no, I'm not going to use TYPEDEF for my structures.
    I do NOT know how to use those haha
*/
// ----DRAWING
// ----PHYSICS
void px_TFALL(PX_Tetrimino* tetrimino){
    if(tetrimino->ft > 4){
        tetrimino->y += 1;
        tetrimino->ft = 0;
    }
    else{
        tetrimino->ft += FTIME * deltatime;
    }
}
void px_TBORDER(PX_Tetrimino* tetrimino, PX_Scene* scene){
    if(tetrimino->y >= GRIDY - 2){
        
        // Playing the sound
        px_SoundSet("res/sounds/drop.wav");
        px_SoundPlay();

        tetrimino->still = true;
    }
}
void px_TDRAW(PX_Tetrimino* tetrimino, PX_Scene* scene, int x, int y, int spriteval){
    // Placeholding someting?
    const int tetdrawtype = tetrimino->type + 1;
    int width;

    // How wide?
    switch(tetrimino->type){
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

    // This is the value of the cell we're trying to get
    int cellv = px_SceneGet(scene, x+tetrimino->x, y+tetrimino->y);

    if( cellv == 0
    ||  cellv == tetdrawtype){
        // Are we still?
        if(tetrimino->still){
            px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y, spriteval * -1);
        }
        else{
            px_ScenePlot(scene, x + tetrimino->x, y + tetrimino->y, spriteval * tetdrawtype);
        }
    }

    // Clearing cells above
    for(int c = 0; c < width; c++){
        px_ScenePlot(scene, c + tetrimino->x, tetrimino->y - 1, 0);
    }
}
void px_TCHECKOTHER(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // This is so that we're able to detect if we're colliding with another block
    // Only the top part will be detected now
    int width;
    int offset;

    // Getting the width of the piece
    switch(tetrimino->type){
    case 1:
    case 2:
    case 5:
        width = 3; offset = 0;      break;
    case 6:
        width = 2; offset = 1;      break;
    case 4:
    case 3:
        width = 2; offset = 0;      break;
    }

    // Go through each column
    for(int c = 0; c < width; c++){
        // What's below us?
        int tilebelow = px_SceneGet(scene, tetrimino->x + c + offset, tetrimino->y + 2);

        if(tilebelow != 0 && tilebelow != tetrimino->type + 1){

            // Playing the sound
            px_SoundSet("res/sounds/drop.wav");
            px_SoundPlay();

            tetrimino->still = true;
        }
    }
}
void px_TPRESERVE(PX_Tetrimino* tetrimino){
    tetrimino->ox = tetrimino->x;
    tetrimino->oy = tetrimino->y;
}

// --REGULARS
PX_Tetrimino px_TetriminoCreate(){
    // Making stuff
    PX_Tetrimino tetrimino;

    // Assigning Variables
    tetrimino.x             = 3;
    tetrimino.y             = 1;
    tetrimino.ox            = 0;
    tetrimino.oy            = 0;
    tetrimino.ft            = 0;
    tetrimino.type          = 1;

    tetrimino.still         = false;

    // Giving back tetrimino
    return tetrimino;
}
void px_TetriminoDelete(PX_Tetrimino* tetrimino){
    free(tetrimino);
}

void px_TetriminoUpdate(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // Are we static?
    if(tetrimino->still)    {return;}

    // Preserve
    px_TPRESERVE(tetrimino);

    // Physics
    px_TFALL(tetrimino);
    px_TCHECKOTHER(tetrimino, scene);

    // Checks
    px_TBORDER(tetrimino, scene);
}
void px_TetriminoDraw(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // Going through each type
    switch(tetrimino->type){
    // The I piece
    case 0:
        // The I Piece is causing big bugs, DELETED :(
        break;

    // The J piece
    case 1:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_J[y*4+x]);
            }
        }
        break;

    // The L piece
    case 2:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_L[y*4+x]);
            }
        }
        break;
    
    // The O piece
    case 3:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_O[y*4+x]);
            }
        }
        break;

    // The S piece
    case 4:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_S[y*4+x]);
            }
        }
        break;
    
    // The T piece
    case 5:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_T[y*4+x]);
            }
        }
        break;
    
    // The Z piece
    case 6:
        for (int y = 0; y < 4; y ++){
            for (int x = 0; x < 4; x ++){
                px_TDRAW(tetrimino, scene, x,y, te_Z[y*4+x]);
            }
        }
        break;
    
    default:
        break;
    }
}
void px_TetriminoMove(PX_Tetrimino* tetrimino, PX_Scene* scene, int x, int y){
    // Moving the wanted tetrimino
    // Getting the width
    int width;

    // What's your type?
    switch(tetrimino->type){
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        width = 3;                      break;
    case 3:
        width = 2;                      break;
    }

    // Can we move?
    if((x < 0 && tetrimino->x + x + 1 > 0) || 
    (x > 0 && tetrimino->x + width + x - 1 < GRIDX)){           // Moving Left and Right but, WITH boundries.
        tetrimino->x += x;

        // Playing a sound
        px_SoundSet("res/sounds/move.wav");
        px_SoundPlay();
    }

    // Clearing cells on the side it was moving away from
    // If this doesn't happen, GLITCHES happen..
    if(x > 0){                          // Moving Right
        for(int y = 0; y < 4; y++){
            // Getting the point
            int cellv = px_SceneGet(scene, tetrimino->x - 1, tetrimino->y + y);
            
            if(cellv == tetrimino->type + 1){
                px_ScenePlot(scene, tetrimino->x - 1, tetrimino->y + y, 0);
            }
        }
    }
    else if(x < 0){                     // Moving Left
        for(int y = 0; y < 4; y++){
            // Getting the point
            int cellv = px_SceneGet(scene, tetrimino->x + width + 1, tetrimino->y + y);
            
            if(cellv == tetrimino->type + 1){
                px_ScenePlot(scene, tetrimino->x + width + 1, tetrimino->y + y, 0);
            }
        }
    }
}
void px_TetriminoDrop(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // Dropping the tetrimino
    // These are our helpers
    bool didDrop = false;
    int height, width, xoff;

    // Whats our height?
    height = tetrimino->y + 1;

    // Whats our width?
    switch(tetrimino->type){
    case 1:
    case 2:
    case 5:
        width = 3; xoff = 0;        break;
    case 4:
    case 3:
        width = 2; xoff = 0;        break;
    case 6:
        width = 2; xoff = 1;        break;
    }

    // Dropping!
    while(!didDrop && !tetrimino->still){
        // Going through the width
        for(int x = 0; x < width; x++){
            // Are we on the ground?
            if(height + 2 > GRIDY){
                didDrop = true;
                tetrimino->still = true;
                break;
            }
            else{
                // What's the pixel below?
                int below = px_SceneGet(scene, tetrimino->x + x + xoff, height + 1);

                // Is it solid?
                if(below == -1){
                    didDrop = true;
                    tetrimino->still = true;
                    break;
                }
            }
        }

        // Did we escape?
        if(didDrop){
            // Playing the sound
            px_SoundSet("res/sounds/slam.wav");
            px_SoundPlay();

            break;
        }
        // KEEP FALLING!
        else{
            // Falling
            tetrimino->y += 1;
            height = tetrimino->y + 1;

            // Drawing so it's consistent
            px_TetriminoDraw(tetrimino, scene);
        }
    }
}
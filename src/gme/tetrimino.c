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
// ----COLLISION
bool px_TCOLLIDING(PX_Tetrimino* tetrimino, PX_Scene* scene){
    for(int y = 0; y < 4; y++){
        // Lets be sure we're not on the ground.
        if(tetrimino->y + y + 1 > GRIDY || tetrimino->y + y - 1 < 0){
            break;
        }

        // All X's
        for(int x = 0; x < 4; x++){
            // Current tile:
            int ctile = px_SceneGet(scene, tetrimino->x + x, tetrimino->y + y);

            // Is this tile VALID
            if(ctile == tetrimino->type + 1){
                // Get the thing below us:
                int belowTile = px_SceneGet(scene, tetrimino->x + x, tetrimino->y + y + 1);

                // Is something below us?
                if(belowTile != 0 && belowTile != tetrimino->type + 1){
                    return true;
                }
            }
        }
    }

    // Not a success
    return false;
}
bool px_TOVEREDGE(PX_Tetrimino* tetrimino, PX_Scene* scene, int xoffset, int yoffset){
    int width, start;

    width = 0; start = 4;

    // What is our width?
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            // What's our cell?
            int ccell = px_SceneGet(scene, tetrimino->x + x, tetrimino->y + y);

            // Is our cell valid
            if(ccell == tetrimino->type + 1){
                // Setting stuff
                if(x < start)   { start = x; }
                if(width < x)   { width = x; }
            }
        }
    }

    // Giving the piece its info
    tetrimino->width = width;

    // Can we move?
    return tetrimino->x + start + xoffset < 0
    || tetrimino->x + width + (xoffset + 1) > GRIDX;
}
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
        if(!tetrimino->dropping){
            px_SoundPlay("res/sounds/tetrimino/drop.wav", 1);
        }

        tetrimino->still = true;
    }
}
void px_TDRAW(PX_Tetrimino* tetrimino, PX_Scene* scene, int x, int y, int spriteval){
    // Placeholding someting?
    const int tetdrawtype = tetrimino->type + 1;
    int width = 0;

    // What is our width?
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

    // Are the cells above avalible?
    if((tetrimino->y - 1) * GRIDY + tetrimino->x > 0){
        // Clearing cells above
        for(int c = 0; c < width; c++){
            px_ScenePlot(scene, c + tetrimino->x, tetrimino->y - 1, 0);
        }
    }
}
void px_TCHECKOTHER(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // This is so that we're able to detect if we're colliding with another block
    // Only the top part will be detected now
    /* 
            -- NEW SYSTEM OF COLLISION!
        This system will account for 
        rotations
    */

    if(px_TCOLLIDING(tetrimino, scene)){
        tetrimino->still = true;
        // The sound
        if(!tetrimino->dropping){
            px_SoundPlay("res/sounds/tetrimino/drop.wav", 1);
        }

        // Are we gamed over?
        if(tetrimino->y <= 2){
            tet_gameOver = true;
        }
    }
}

// --REGULARS
PX_Tetrimino px_TetriminoCreate(){
    // Making stuff
    PX_Tetrimino tetrimino;

    // Assigning Variables
    tetrimino.x             = 3;
    tetrimino.y             = 1;
    tetrimino.width         = 0;
    tetrimino.ft            = 0;
    tetrimino.type          = 1;

    tetrimino.still         = false;
    tetrimino.dropping      = false;

    tet_gameOver            = false;

    // Giving back tetrimino
    return tetrimino;
}
void px_TetriminoDelete(PX_Tetrimino* tetrimino){
    free(tetrimino);
}
void px_TetriminoReset(PX_Tetrimino* tetrimino){
    tetrimino->still        = false;
    tetrimino->dropping     = false;
    tetrimino->y            = 0;
    tetrimino->x            = 3;
    tetrimino->ft           = 0;
    tetrimino->type         += 1;
    tetrimino->rotation     = 0;

    if(tetrimino->type >= 7) {tetrimino->type = 1;}
}
void px_TetriminoUpdate(PX_Tetrimino* tetrimino, PX_Scene* scene){
    // Are we static?
    if(tetrimino->still)    {printf("STILL\n"); return;}

    // Physics
    px_TFALL(tetrimino);
    px_TCHECKOTHER(tetrimino, scene);

    // Checks
    px_TBORDER(tetrimino, scene);
}
void px_TetriminoDraw(PX_Tetrimino* tetrimino, PX_Scene* scene){
    /*
            Rotations, are complicated.
            Let's use a little cheat to get through it!
    */

    // Going through X and Y
    for (int wy = 0; wy < 4; wy ++){
        for (int wx = 0; wx < 4; wx ++){
            // Sorting out the rotation stuff
            int x,y;

            // Flipping?
            switch(tetrimino->rotation){
            case 0:         // Up
                x = wx;
                y = wy;
                break;
            case 1:         // Right
                x = wy;
                y = 2 - wx;
                break;
            case 2:         // Down
                x = 2 - wx;
                y = 2 - wy;
                break;
            case 3:         // Left
                x = 2 - wy;
                y = wx;
                break;
            }

            // Going through each type
            switch(tetrimino->type){
            // The I piece
            case 0:
                px_TDRAW(tetrimino, scene, wx,wy, te_I[y*4+x]);
                break;

            // The J piece
            case 1:
                px_TDRAW(tetrimino, scene, wx,wy, te_J[y*4+x]);
                break;

            // The L piece
            case 2:
                px_TDRAW(tetrimino, scene, wx,wy, te_L[y*4+x]);
                break;
    
            // The O piece
            case 3:
                px_TDRAW(tetrimino, scene, wx,wy, te_O[y*4+x]);
                break;

            // The S piece
            case 4:
                px_TDRAW(tetrimino, scene, wx,wy, te_S[y*4+x]);
                break;
    
            // The T piece
            case 5:
                px_TDRAW(tetrimino, scene, wx,wy, te_T[y*4+x]);
                break;
    
            // The Z piece
            case 6:
                px_TDRAW(tetrimino, scene, wx,wy, te_Z[y*4+x]);
                break;
    
            default:
                break;
            }
        }
    }
}
void px_TetriminoMove(PX_Tetrimino* tetrimino, PX_Scene* scene, int x, int y){
    // Moving the wanted tetrimino
    // Appropriate?
    if(px_TOVEREDGE(tetrimino, scene, x, 0)) {return;}

    // Moving
    tetrimino->x += x;

    // Playing a sound
    px_SoundPlay("res/sounds/tetrimino/move.wav", 1);

    // Clearing cells on the side it was moving away from
    // If this doesn't happen, GLITCHES happen..
    if(x > 0){                          // Moving Right
        for(int y = 0; y < 4; y++){
            // Getting the point
            int cellv = px_SceneGet(scene, tetrimino->x - 1, tetrimino->y + y - 1);
            
            if(cellv == tetrimino->type + 1){
                px_ScenePlot(scene, tetrimino->x - 1, tetrimino->y + y - 1, 0);
            }
        }
    }
    else if(x < 0){                     // Moving Left
        // Are we going to cause a index out of range crash?
        if((tetrimino->y - 1) * GRIDY + tetrimino->x > 0){
            for(int y = 0; y < 4; y++){
                // Getting the point
                int cellv = px_SceneGet(scene, tetrimino->x + tetrimino->width + 1, tetrimino->y + y);
            
                if(cellv == tetrimino->type + 1){
                    px_ScenePlot(scene, tetrimino->x + tetrimino->width + 1, tetrimino->y + y, 0);
                }
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

    // Avalible points?
    if(tetrimino->y * GRIDY + tetrimino->x > 0){
        // Resetting surrounding graphics
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                if(px_SceneGet(scene, tetrimino->x + x, tetrimino->y + y - 1) == tetrimino->type + 1){
                    px_ScenePlot(scene, tetrimino->x + x, tetrimino->y + y - 1, 0);
                }
            }
        }
    }

    // Dropping!
    while(!didDrop && !tetrimino->still){
        // Going through the width
        for(int x = 0; x < width; x++){
            // Are we on the ground?
            if(height + 2 > GRIDY){
                didDrop = true;
                break;
            }
            else{
                // Checking others
                if(px_TCOLLIDING(tetrimino, scene)){
                    didDrop = true;
                    break;
                }
            }
        }

        // Did we escape?
        if(didDrop){
            // Playing the sound
            px_SoundPlay("res/sounds/tetrimino/slam.wav", 1);

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

    // We're still
    // So play the cool sound!
    tetrimino->dropping = true;
    // Drop imidiatly.
    tetrimino->ft = 4;
    // Just to buffer
    SDL_Delay(25);
}
void px_TetriminoRotate(PX_Tetrimino* tetrimino, PX_Scene* scene, int direction){
    // Dumb types
    if(tetrimino->type == 3)    {return;}

    // Are we avalible to turn?
    if(px_TOVEREDGE(tetrimino, scene, direction, 0)) {return;}

    // Rotating
    tetrimino->rotation += direction;

    // Clamping
    if(tetrimino->rotation < 0){
        tetrimino->rotation = 3;
    }
    if(tetrimino->rotation > 3){
        tetrimino->rotation = 0;
    }

    // New rotation?
    printf("Rotation: %i\n", tetrimino->rotation);
}
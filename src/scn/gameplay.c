// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "gameplay.h"

// Functions
// --HELPER
void game_MoveTetrimino(){
    const Uint8* ks = SDL_GetKeyboardState(NULL);

    if(!didpress){
        if(ks[SDL_SCANCODE_LEFT]){
            // TODO: IMPLEMENT
            px_TetriminoMove(&tetrimino, &scene, -1, 0);
        }
        else if(ks[SDL_SCANCODE_RIGHT]){
            // TODO: IMPLEMENT
            px_TetriminoMove(&tetrimino, &scene, +1, 0);
        }
        else if(ks[SDL_SCANCODE_DOWN]){
            px_TetriminoMove(&tetrimino, &scene, 0, +2);
        }
        else if(ks[SDL_SCANCODE_SPACE]){
            px_TetriminoDrop(&tetrimino, &scene);
        }
        else if(ks[SDL_SCANCODE_Z]){
            didpress = true;
            px_TetriminoRotate(&tetrimino, -1);
        }
        else if(ks[SDL_SCANCODE_X]){
            didpress = true;
            px_TetriminoRotate(&tetrimino, 1);
        }
        else{
            // No keys, Do nothing!
            return;
        }

        // We did press a key
        didpress = true;
    }
    else if((!ks[SDL_SCANCODE_LEFT]) 
    && (!ks[SDL_SCANCODE_RIGHT]) 
    && (!ks[SDL_SCANCODE_DOWN])
    && (!ks[SDL_SCANCODE_SPACE])){
        didpress = false;
    }
}

// --HEADER
void blk_GameStart(SDL_Renderer* renderer){
    // Making a scene
    scene = px_SceneCreate(renderer, 300, 512);
    tetrimino = px_TetriminoCreate();
}
void blk_GameUpdate(){
    px_TetriminoUpdate(&tetrimino, &scene);
        if(tetrimino.still){
        /*
                -- THIS CODE WOULD DO THIS --
            It would "delete" the current block,
            and place it to the top of the screen.
        */
        
        // This part of the code will spawn in a NEW block and keep the old one!
        px_TetriminoDraw(&tetrimino, &scene);
        px_TetriminoReset(&tetrimino);
    }

    // Moving the tetrimino
    game_MoveTetrimino();
}
void blk_GameDraw(SDL_Renderer* renderer){
    // World drawing and Scene drawing
    px_TetriminoDraw(&tetrimino, &scene);
    px_SceneDraw(&scene, renderer);
}
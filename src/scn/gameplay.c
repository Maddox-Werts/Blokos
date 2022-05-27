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
            didpress = true;
        }
        else if(ks[SDL_SCANCODE_RIGHT]){
            // TODO: IMPLEMENT
            px_TetriminoMove(&tetrimino, &scene, +1, 0);
            didpress = true;
        }
        else if(ks[SDL_SCANCODE_DOWN]){
            didpress = true;
            px_TetriminoMove(&tetrimino, &scene, 0, +2);
        }
        else if(ks[SDL_SCANCODE_SPACE]){
            didpress = true;
            px_TetriminoDrop(&tetrimino, &scene);
        }
        else{
            // No keys, Do nothing!
        }
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
    scene = px_SceneCreate(300, 512);
    tetrimino = px_TetriminoCreate();
}
void blk_GameUpdate(){
    px_TetriminoUpdate(&tetrimino, &scene);
        if(tetrimino.still){
        /*
                -- THIS CODE WOULD DO THIS --
            It would "delete" the current block,
            and place it to the top of the screen.
            ======================================
            tetrimino.still = false;
            tetrimino.type += 1;
            tetrimino.y = 0;

            if(tetrimino.type >= 7) {tetrimino.type = 0;}
        */
        
        // This part of the code will spawn in a NEW block and keep the old one!
        px_TetriminoDraw(&tetrimino, &scene);
        tetrimino.still = false;
        tetrimino.type += 1;
        tetrimino.y = 1;

        if(tetrimino.type >= 7) {tetrimino.type = 1;}
    }

    // Moving the tetrimino
    game_MoveTetrimino();
}
void blk_GameDraw(SDL_Renderer* renderer){
    // World drawing and Scene drawing
    px_TetriminoDraw(&tetrimino, &scene);
    px_SceneDraw(&scene, renderer);

    // Drawing the score
    
}
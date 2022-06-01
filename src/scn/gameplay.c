// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "gameplay.h"
#include "../gme/monster.h"

// Variables
PX_Monster monster;

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
            px_TetriminoRotate(&tetrimino, -1);
        }
        else if(ks[SDL_SCANCODE_X]){
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
    && (!ks[SDL_SCANCODE_SPACE])
    && (!ks[SDL_SCANCODE_Z])
    && (!ks[SDL_SCANCODE_X])){
        didpress = false;
    }
}
void game_UpdateScore(SDL_Renderer* renderer){
    // A color?
    SDL_Color fg = {
        255,255,255, 255
    };

    // New Score
    char* nst[10];
    sprintf(nst, "%d", scene.score);

    // Making surface
    if(! (score_num_txt.surface = TTF_RenderText_Solid(score_num_txt.font, nst, fg))){
        printf("Failed to update Score(number) Surface\n");
        return;
    }

    // Updating the texture
    if(! (score_num_txt.texture = SDL_CreateTextureFromSurface(renderer, score_num_txt.surface))){
        printf("Failed to update Score(number) Texture\n");
        return;
    }

    score_num_txt.width = score_num_txt.surface->w;

    // Cleanup
    SDL_FreeSurface(score_num_txt.surface);
}

// --HEADER
void blk_GameStart(SDL_Renderer* renderer){
    // Making a scene
    scene = px_SceneCreate(renderer, 300, 512);
    tetrimino = px_TetriminoCreate();

    // Making other elements
    score_txt = px_TextCreate(renderer, "SCORE: ");
    score_num_txt = px_TextCreate(renderer, "0");

    // Making entities
    monster = px_MonsterCreate(renderer);
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

    // Updating Entities
    px_MonsterUpdate(&monster, &scene);
}
void blk_GameDraw(SDL_Renderer* renderer){
    // World drawing and Scene drawing
    px_TetriminoDraw(&tetrimino, &scene);
    px_SceneDraw(&scene, renderer);

    // Text Updates
    game_UpdateScore(renderer);

    px_TextDraw(renderer, score_txt, 300, 150, 112, 40);
    px_TextDraw(renderer, score_num_txt, 400, 150, (int)(score_num_txt.width * 1.5f), 40);

    // Drawing entities
    px_MosnterDraw(renderer, &scene, &monster);
}
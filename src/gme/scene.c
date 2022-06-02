// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "scene.h"
#include "../app/texture.h"
#include "../app/sound.h"
#include "../app/dtime.h"

// Functions

// Variables
int redRows = 0;
float redTime = 0;

// --HEADER
PX_Scene px_SceneCreate(SDL_Renderer* renderer, int width, int height){
    // Making the structure
    PX_Scene scene = {
        {
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,
        },
        width, height,
        0
    };

    // Setting something Important
    gameOver = false;
    redRows = 0;
    redTime = 0;

    // Loading textures
    celltex = px_TextureCreate(renderer, "res/sprites/cell.png");
    SDL_SetTextureBlendMode(celltex, SDL_BLENDMODE_BLEND);

    return scene;
}
void px_SceneDelete(PX_Scene* scene){
    free(scene);
}

void px_ScenePlot(PX_Scene* scene, int x, int y, int value){
    // Plotting based on thing
    scene->matricies[y*GRIDX+x] = value;
}
int px_SceneGet(PX_Scene* scene, int x, int y){
    return scene->matricies[y*GRIDX+x];
}
void px_SceneDraw(PX_Scene* scene, SDL_Renderer* renderer){
    // Drawing our scene every x&y coords
    for(int y = 0; y < GRIDY; y++){
        // For the awesomeness!
        int cellsfilled = 0;

        for(int x = 0; x < GRIDX; x++){
            // Helpers
            bool filled;

            // Color
            SDL_SetRenderDrawColor(renderer, 134,134,134, 1);

            // Game over?
            if(gameOver){
                if(y <= redRows){
                    filled = true;
                    SDL_SetRenderDrawColor(renderer, 255, 55, 55, 1);
                    SDL_SetTextureColorMod(celltex, 255, 55, 55);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 134,134,134, 1);
                    SDL_SetTextureColorMod(celltex, 134, 134, 134);
                }

                if(redTime >= 240.0f){
                    redTime = 0;
                    redRows += 1;
                }
                else{
                    redTime += deltatime * (120.0f/1000.0f);
                }
            }
            else{
                // Setting color
                // What type of cell is it?
                if(scene->matricies[y*GRIDX+x] == -1){
                    SDL_SetTextureColorMod(celltex, 200,200,200);
                    cellsfilled += 1;
                    filled = true;
                }
                else if(scene->matricies[y*GRIDX+x] != 0){
                    SDL_SetTextureColorMod(celltex, 255,255,255);
                    filled = true;
                }
                else{
                    SDL_SetTextureColorMod(celltex, 100,100,100);
                    filled = false;
                }
            }

            // Getting the size difference from window
            const int _xgrid = scene->width  / GRIDX;
            const int _ygrid = scene->height / GRIDY;

            // Making the rectangle
            SDL_Rect rect;

            // Placing rect
            rect.x = x * _xgrid;
            rect.y = y * _ygrid;
            rect.w = _xgrid; rect.h = _ygrid;

            // Drawing rect
            if(filled){
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderCopy(renderer, celltex, NULL, &rect);
            }
            else{
                SDL_RenderDrawRect(renderer, &rect);
            }

            // Clear board!
            // -- USELESS CODE!
            // Making it so that it'll be able
            // to hold all prior cells

            // scene->matricies[y*GRIDX+x] = 0;
        }
    
        // Were all the cells filled?
        if(cellsfilled >= GRIDX){
            // Playing the sound
            px_SoundPlay("res/sounds/clear.wav", 0);

            // Clearing rows
            for(int cy = y; cy > 0; cy--){
                for(int x = 0; x < GRIDX; x++){
                    scene->matricies[cy*GRIDX+x] = scene->matricies[(cy-1)*GRIDX+x];
                }
            }

            // The effect
            for(int ts = 0; ts < 3; ts++){
                for(int x = 0; x < GRIDX; x++){
                    // Effect Color
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);

                    // Getting the size difference from window
                    const int _xgrid = scene->width  / GRIDX;
                    const int _ygrid = scene->height / GRIDY;

                    // Making the rectangle
                    SDL_Rect rect;

                    // Placing rect
                    rect.x = x * _xgrid;
                    rect.y = y * _ygrid;
                    rect.w = _xgrid; rect.h = _ygrid;

                    SDL_RenderFillRect(renderer, &rect);

                    // Drawing cool things
                    SDL_RenderPresent(renderer);
                    SDL_Delay(20);
                }
            }

            // Points?
            scene->score += 100;
            printf("New Score: %i\n", scene->score);
        }
    }
}
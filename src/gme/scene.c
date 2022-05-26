// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "scene.h"

// Functions
struct PX_Scene px_SceneCreate(int width, int height){
    // Making the structure
    struct PX_Scene scene = {
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
        width, height
    };

    return scene;
}
void px_SceneDelete(struct PX_Scene* scene){
    free(scene);
}

void px_ScenePlot(struct PX_Scene* scene, int x, int y, int value){
    // Plotting based on thing
    scene->matricies[y*GRIDX+x] = value;
}
int px_SceneGet(struct PX_Scene* scene, int x, int y){
    return scene->matricies[y*GRIDX+x];
}
void px_SceneDraw(struct PX_Scene* scene, SDL_Renderer* renderer){
    // Drawing our scene every x&y coords
    for(int y = 0; y < GRIDY; y++){
        for(int x = 0; x < GRIDX; x++){
            // Helpers
            bool filled;

            // Setting color
            // What type of cell is it?
            if(scene->matricies[y*GRIDX+x] != 0){
                SDL_SetRenderDrawColor(renderer, 134,135,200, 1);
                filled = true;
            }
            else{
                SDL_SetRenderDrawColor(renderer, 100,100,100, 1);
                filled = false;
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
    }
}
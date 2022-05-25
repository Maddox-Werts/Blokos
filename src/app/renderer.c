// Files
// --SYSTEM
#include <stdio.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "renderer.h"

// Functions
SDL_Renderer* px_RendererCreate(SDL_Window* window){
    // Making a renderer from the window
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 0, SDL_RENDERER_ACCELERATED
    );

    // Was the renderer made?
    if(renderer == NULL){
        printf("Failed to create renderer!\n");
    }

    return renderer;
}
void px_RendererDelete(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    free(renderer);
}

void px_RendererClear(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0,0,0, 1);
    SDL_RenderClear(renderer);
}
void px_RendererDisplay(SDL_Renderer* renderer){
    SDL_RenderPresent(renderer);
}
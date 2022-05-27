// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "mainmenu.h"

// Functions
// --HELPERS
void blk_CREATETITLE(SDL_Renderer* renderer){
    // Getting the Title Info stuff
    SDL_Surface* titlesurf;

    // was the surface loaded?
    if(!(titlesurf = IMG_Load("res/sprites/blk_title.png"))){
        printf("Failed to load Title Image!\n");
    }

    // Converting surface to texture
    if(!(titletex = SDL_CreateTextureFromSurface(renderer, titlesurf))){
        printf("Failed to create texture from surface!\n");
    }

    // Cleanup
    SDL_FreeSurface(titlesurf);
}

// --BASE
void blk_MMCreate(SDL_Renderer* renderer){
    // Init SDL2_IMG
    IMG_Init(IMG_INIT_PNG);

    // Creating textures and what not
    blk_CREATETITLE(renderer);
}
void blk_MMUpdate(){

}
void blk_MMDraw(SDL_Renderer* renderer){
    // Making the title card
    SDL_Rect titlecard;

    titlecard.x = 100; titlecard.y = 10;
    titlecard.w = 300; titlecard.h = 300;

    SDL_RenderFillRect(renderer, &titlecard);
    SDL_RenderCopy(renderer, titletex, NULL, &titlecard);
}
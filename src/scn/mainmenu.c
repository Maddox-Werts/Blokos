// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "../app/texture.h"
#include "mainmenu.h"

// Functions
// --BASE
void blk_MMCreate(SDL_Renderer* renderer){
    // Init SDL2_IMG
    IMG_Init(IMG_INIT_PNG);

    // Creating textures and what not
    titletex = px_TextureCreate(renderer, "res/sprites/title.png");
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
// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "../app/texture.h"
#include "../app/text.h"
#include "mainmenu.h"

// Functions
// --BASE
void blk_MMCreate(SDL_Renderer* renderer){
    // Init SDL2_IMG
    IMG_Init(IMG_INIT_PNG);

    // Creating textures and what not
    titletex = px_TextureCreate(renderer, "res/sprites/title.png");

    // Making the title thing
    start_txt = px_TextCreate(renderer, "Press [SPACE] to start.");
}
void blk_MMUpdate(){

}
void blk_MMDraw(SDL_Renderer* renderer){
    // Color
    SDL_SetRenderDrawColor(renderer, 0,0,0, 1);

    // Making the title card
    SDL_Rect titlecard;

    titlecard.x = 100; titlecard.y = 10;
    titlecard.w = 300; titlecard.h = 300;

    SDL_RenderFillRect(renderer, &titlecard);
    SDL_RenderCopy(renderer, titletex, NULL, &titlecard);

    // Making the start text
    px_TextDraw(renderer, start_txt, 100, 350, 300, 50);
}
void blk_MMClean(){
    SDL_FreeSurface(start_txt.surface);
}
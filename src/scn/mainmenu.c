// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "../app/features.h"
#include "../app/texture.h"
#include "../app/dtime.h"
#include "../app/text.h"
#include "mainmenu.h"

// Variables
float _time;
float stpos;

// Functions
// --HELPER
void blk_MMSTART(){
    stpos = Lerp(stpos, 350, 0.05f);

    if(stpos <= 353){
        stpos = 350;
        px_mcanstart = true;
    }
}

// --BASE
void blk_MMCreate(SDL_Renderer* renderer){
    // Init SDL2_IMG
    IMG_Init(IMG_INIT_PNG);

    // Creating textures and what not
    titletex = (SDL_Texture*)malloc(16 * sizeof(int));
    titletex = px_TextureCreate(renderer, "res/sprites/title.png");

    // Making the title thing
    start_txt = px_TextCreate(renderer, "Press [SPACE] to start.");

    // Making the time
    _time = 0;
    stpos = 600;
    px_mcanstart = false;
}
void blk_MMUpdate(){
    // Adding time
    _time += (float)deltatime * 1.2f;

    // Allowing the menu to transition
    blk_MMSTART();
}
void blk_MMDraw(SDL_Renderer* renderer){
    // Color
    SDL_SetRenderDrawColor(renderer, 0,0,0, 1);

    // Making the title card
    SDL_Rect titlecard;

    titlecard.x = 100 + (int)(cosf(_time / 200) * 10); 
    titlecard.y = 10 + (int)(sinf(_time / 100) * 10);
    titlecard.w = 300; titlecard.h = 300;

    SDL_RenderFillRect(renderer, &titlecard);
    SDL_RenderCopy(renderer, titletex, NULL, &titlecard);

    // Making the start text
    px_TextDraw(renderer, start_txt, 100, stpos, 300, 50);
}
void blk_MMClean(){
    SDL_FreeSurface(start_txt.surface);
    free(titletex);
}
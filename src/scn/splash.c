// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "splash.h"
#include "../app/features.h"
#include "../app/texture.h"
#include "../app/dtime.h"
#include "../app/sound.h"

// Variables
SDL_Texture* splashtex;

int wid, hig;
int spx,spy;
int spf;

bool fading, playedding;

// Functions
void px_SSstart(SDL_Renderer* renderer, int width, int height){
    // Making a texture
    splashtex = (SDL_Texture*)malloc(32 * sizeof(int));
    splashtex = px_TextureCreate(renderer, "res/sprites/primax.png");
    SDL_SetTextureBlendMode(splashtex, SDL_BLENDMODE_BLEND);
    
    // Setting variables
    px_ssready = false;
    playedding = false;
    fading = false;

    wid = width; hig = height;

    spx = (int)(width / 2);
    spy = (int)(height * 1.5f);

    spf = 255;
}
void px_SSupdate(){
    // Moving the logo to center
    spy = Lerp(spy, hig / 2, 0.05f);

    // Are we ready?
    if(abs(spy - (hig / 2)) <= 5) {fading = true;}  // Fade start
    if(abs(spy - (hig / 2)) <= 15) {                // Play Ba-Ding
        if(!playedding){
            px_SoundPlay("res/sounds/primaxding.wav", 0);
            playedding = true;
        }
    }
    if(fading){                                     // Fading
        spf = Lerp(spf, 0, 0.02f * deltatime);
        printf("Alpha: %i\n", spf);
        if(spf <= 3) {px_ssready = true;}
    }
}
void px_SSdraw(SDL_Renderer* renderer, int width, int height){
    // The clear color
    SDL_SetRenderDrawColor(renderer, 0,0,0, 1);

    // Making the rect
    SDL_Rect rect;

    // Constants
    const int rsize = 400;

    // Setting the positional stuff
    rect.w = rsize; rect.h = rsize;
    rect.x = spx - (int)(rsize / 2.0f);
    rect.y = spy - (int)(rsize / 2.0f);

    SDL_SetTextureAlphaMod(splashtex, spf);

    // Drawing the rectangle
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, splashtex, NULL, &rect);
}
void px_SSclean(){
    // Free All variables
    free(splashtex);
}
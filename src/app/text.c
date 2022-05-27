// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// --HEADERS
#include "text.h"

// Functions
PX_Text px_TextCreate(SDL_Renderer* renderer, const char* msg){
    // Making the holding structure
    PX_Text holdtext;

    // Getting and Creating a font
    TTF_Font* font = TTF_OpenFont("res/fonts/mono.ttf", 32);

    // Was the font opened?
    if(font == NULL){
        printf("Could not open font!\n");
    }

    // Getting a color
    SDL_Color clr = {
        255,255,255,1
    };

    SDL_Surface* surf = TTF_RenderText_Solid(font, msg, clr);
    SDL_Texture* text = SDL_CreateTextureFromSurface(
        renderer, surf
    );

    // Assigning stuff
    holdtext.font = font;
    holdtext.surface = surf;
    holdtext.texture = text;
}
void px_TextDraw(SDL_Renderer* renderer, PX_Text text, int x, int y, int w, int h){
    // Holding variable
    SDL_Rect rect;

    // Color
    SDL_SetRenderDrawColor(renderer, 255,255,255, 1);

    // Giving rect stuff
    rect.x = x; rect.y = y;
    rect.w = w; rect.h = h;

    // Rendering
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, text.texture, NULL, &rect);
}
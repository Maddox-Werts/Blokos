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
    // Starting TTF system
    TTF_Init();

    // Making the holding structure
    PX_Text holdtext;

    // Holders/Helpers
    SDL_Surface* surf;
    SDL_Texture* text;
    TTF_Font* font;

    // Was the font opened?
    if(!(font = TTF_OpenFont("res/fonts/default.ttf", 16))){
        printf("Could not open font!\n");
    }

    // Getting a color
    SDL_Color txt_color = {
        255,255,255, 255
    };

    // DEBUG
    printf("Your message: %s.\n", msg);

    if( !(surf = TTF_RenderText_Solid(font, msg, txt_color)) ){
        printf("Failed to create Render Text\n");
    }
    if( !(text = SDL_CreateTextureFromSurface(renderer, surf)) ){
        printf("Failed to create Render Text Texture\n");
    }

    // Assigning stuff
    holdtext.font = font;
    holdtext.surface = surf;
    holdtext.texture = text;

    // Giving result
    return holdtext;
}
void px_TextDraw(SDL_Renderer* renderer, PX_Text text, int x, int y, int w, int h){
    // Holding variable
    SDL_Rect rect;

    // Color
    SDL_SetRenderDrawColor(renderer, 0,0,0, 1);

    // Giving rect stuff
    rect.x = x; rect.y = y;
    rect.w = w; rect.h = h;

    // Rendering
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderCopy(renderer, text.texture, NULL, &rect);
}
// Define once
#ifndef H_TEXT
#define H_TEXT

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Structures
typedef struct PX_Text{
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;

    int width;
} PX_Text;

// Functions
PX_Text px_TextCreate(SDL_Renderer* renderer, const char* msg);
void px_TextDraw(SDL_Renderer* renderer, PX_Text text, int x, int y, int w, int h);

// End if
#endif
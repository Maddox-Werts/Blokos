// Define Once
#ifndef H_RENDERER
#define H_RENDERER

// Files
// --SYSTEM
// --SDL
#include <SDL2/SDL.h>
// --HEADERS

// Functions
SDL_Renderer* px_RendererCreate(SDL_Window* window);
void px_RendererDelete(SDL_Renderer* renderer);

void px_RendererClear(SDL_Renderer* renderer);
void px_RendererDisplay(SDL_Renderer* renderer);

// End definition
#endif
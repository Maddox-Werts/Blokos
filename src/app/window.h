// Define once
#ifndef H_WINDOW
#define H_WINDOW

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS

// Structures
struct PX_Window{
    SDL_Window* window;
    int width, height;
    bool opened;
};

// Functions
struct PX_Window px_WindowCreate(const char* title, int width, int height);
void px_WindowDelete(struct PX_Window* window);

void px_WindowUpdate(struct PX_Window* window);

// End definition
#endif
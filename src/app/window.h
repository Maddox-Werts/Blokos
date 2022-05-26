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
typedef struct PX_Window{
    SDL_Window* window;
    int width, height;
    bool opened;
} PX_Window;

// Functions
PX_Window px_WindowCreate(const char* title, int width, int height);
void px_WindowDelete(PX_Window* window);

void px_WindowUpdate(PX_Window* window);

// End definition
#endif
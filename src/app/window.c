// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "window.h"

/*
    -- THIS IS FOR THE WINDOW! --
*/

// Functions
PX_Window px_WindowCreate(const char* title, int width, int height){
    // Starting some things
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);

    // Making the holding structure
    PX_Window window;

    // Creating a window
    window.window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, 
        SDL_WINDOW_SHOWN
    );

    // Was the window created?
    if(window.window == NULL){
        printf("Failed to create window!\n");
    }

    // Setting others
    window.width = width;
    window.height = height;
    window.opened = true;

    // Returning Window
    return window;
}
void px_WindowDelete(PX_Window* window){
    SDL_DestroyWindow(window->window);
    free(window);
}

void px_WindowUpdate(PX_Window* window){
    // Making an event holder
    SDL_Event ev;

    // Polling through events
    while(SDL_PollEvent(&ev)){
        // Going through all types
        switch(ev.type){
        // Pressing the X button
        case SDL_QUIT:
            window->opened = false;
            break;
        // Pressing Escape
        case SDL_KEYDOWN:
            if(ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { window->opened = false; }
            break;
        }
    }
}
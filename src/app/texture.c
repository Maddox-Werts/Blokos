// Files
// --SYSTEM
#include <stdio.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "texture.h"

// Functions
SDL_Texture* px_TextureCreate(SDL_Renderer* renderer, const char* file){
    // Helpers
    SDL_Texture* result;
    SDL_Surface* texsurf;

    // Was the surface loaded?
    if(!(texsurf = IMG_Load(file))){
        printf("Failed to load Texture Image: %s.\n", file);
    }

    // Converting surface to texture
    if(!(result = SDL_CreateTextureFromSurface(renderer, texsurf))){
        printf("Failed to create texture from surface!\n");
    }

    // Cleanup
    SDL_FreeSurface(texsurf);

    // Returning Result
    return result;
}
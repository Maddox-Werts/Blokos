// Define Once
#ifndef H_SOUND
#define H_SOUND

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Variables
Mix_Chunk* currentsound;

// Functions
void px_SoundStart();
void px_SoundSet(const char* file);
void px_SoundPlay();

// End definition
#endif
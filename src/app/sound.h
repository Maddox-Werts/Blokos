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
Mix_Chunk* backgroundsound;
Mix_Chunk* playersound;
Mix_Chunk* entitysound;

// Functions
void px_SoundStart();
void px_SoundPlay(const char* file, int type);

// End definition
#endif
// Files
// --SYSTEM
#include <stdio.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
// --HEADERS
#include "sound.h"

// Variables
int totalSounds = 0;

// Functions
void px_SoundStart(){
    // Values
    const Uint16 a_format = AUDIO_S16SYS;
    const int a_rate = 22050;
    const int a_channels = 2;
    const int a_buffers = 4096;

    // Opening a sound
    if((Mix_OpenAudio(a_rate, a_format, a_channels, a_buffers))){
        printf("Failed to load Audio Systems!\n");
    }
    else{
        printf("Audio Systems started successfuly!\n");
    }
}
void px_SoundSet(const char* file){
    // Freeing previous sound
    Mix_FreeChunk(currentsound);

    // Getting the audio file
    Mix_Chunk* tchunk = Mix_LoadWAV(file);
    if(!tchunk){
        printf("Failed to load Audio File!\n");
        return;
    }

    // Setting the current sound
    currentsound = tchunk;
}
void px_SoundPlay(){
    if(!currentsound){
        printf("The current sound does not exist!\n");
        return;
    }
    Mix_PlayChannel(-1, currentsound, 0);
}
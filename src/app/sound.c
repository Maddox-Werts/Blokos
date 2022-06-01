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
void px_SoundPlay(const char* file, int type){
    // Holding
    Mix_Chunk* chnk;

    // Freeing previous sound
    switch(type){
    case 0:             // Background Sounds
        Mix_FreeChunk(backgroundsound);
        break;
    case 1:             // Player Sounds
        Mix_FreeChunk(playersound);
        break;
    case 2:             // Entity Sounds
        Mix_FreeChunk(entitysound);
        break;
    }

    // Getting the audio file
    Mix_Chunk* tchunk = Mix_LoadWAV(file);
    if(!tchunk){
        printf("Failed to load Audio File!\n");
        return;
    }

    // Setting the current sound
    switch(type){
    case 0:             // Background Sounds

        backgroundsound = tchunk;

        // Playing the sound
        if(!backgroundsound){
            printf("The current sound does not exist!\n");
            return;
        }
        Mix_PlayChannel(-1, backgroundsound, 0);

        break;
    case 1:             // Player Sounds
        playersound = tchunk;

        // Playing the sound
        if(!playersound){
            printf("The current sound does not exist!\n");
            return;
        }
        Mix_PlayChannel(-1, playersound, 0);

        break;
    case 2:             // Entity Sounds
        entitysound = tchunk;

        // Playing the sound
        if(!entitysound){
            printf("The current sound does not exist!\n");
            return;
        }
        Mix_PlayChannel(-1, entitysound, 0);

        break;
    }
}
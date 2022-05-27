// Define once
#ifndef H_SCENE
#define H_SCENE

// Files
// --SYSTEM
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// --HEADERS
#include "tetriminos.h"
#include "../app/sound.h"

/*
    For this, The scene will be a 
    9x16 grid = 144
*/

// CONSTANTS
#define GRIDX 9
#define GRIDY 16

// Structure
typedef struct PX_Scene{
    int matricies[144];
    int width, height;

    int SCORE;
} PX_Scene;

// Variables
bool gameOver;
SDL_Texture* celltex;

// Functions
PX_Scene px_SceneCreate(SDL_Renderer* renderer, int width, int height);
void px_SceneDelete(PX_Scene* scene);

void px_ScenePlot(PX_Scene* scene, int x, int y, int value);
int px_SceneGet(PX_Scene* scene, int x, int y);
void px_SceneDraw(PX_Scene* scene, SDL_Renderer* renderer);

// End definition
#endif
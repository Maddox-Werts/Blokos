// Define once
#ifndef H_SCENE
#define H_SCENE

// Files
// --SYSTEM
// --SDL
#include <SDL2/SDL.h>
// --HEADERS
#include "tetriminos.h"


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

// Functions
PX_Scene px_SceneCreate(int width, int height);
void px_SceneDelete(PX_Scene* scene);

void px_ScenePlot(PX_Scene* scene, int x, int y, int value);
int px_SceneGet(PX_Scene* scene, int x, int y);
void px_SceneDraw(PX_Scene* scene, SDL_Renderer* renderer);

// End definition
#endif
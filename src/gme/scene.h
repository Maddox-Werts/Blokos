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
struct PX_Scene{
    int matricies[144];
    int width, height;
};

// Functions
struct PX_Scene px_SceneCreate(int width, int height);
void px_SceneDelete(struct PX_Scene* scene);

void px_ScenePlot(struct PX_Scene* scene, int x, int y, int value);
int px_SceneGet(struct PX_Scene* scene, int x, int y);
void px_SceneDraw(struct PX_Scene* scene, SDL_Renderer* renderer);

// End definition
#endif
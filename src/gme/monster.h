// Define once
#ifndef H_MONSTER
#define H_MONSTER

// Files
// --SYSTEM
#include <stdbool.h>
// --SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --HEADERS
#include "../gme/scene.h"
#include "../app/texture.h"
#include "../app/dtime.h"

// Structures
typedef struct PX_Monster{
    int x; int y;
    bool grounded;
    bool active;
} PX_Monster;

// Variables
SDL_Texture* monster_tex;

// Functions
PX_Monster px_MonsterCreate(SDL_Renderer* renderer);
void px_MonsterUpdate(PX_Monster* monster, PX_Scene* scene);
void px_MosnterDraw(SDL_Renderer* renderer, PX_Scene* scene, PX_Monster* monster);

// End definition
#endif
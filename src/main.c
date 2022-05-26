/*
        -- BLOKOS -- 
    A simple Tetris Re-Make for my Computer Science
    class In May of 2022. I'm going to choose the 
    C language, because it makes the Most sense to me.
    My code may be a little sloppy, so if there's anything horrible,
    feel free to let me know!
*/

// For SDL(WINDOWS)
#define SDL_MAIN_HANDLED

// Files
// --SYSTEM
#include <stdio.h>
#include <stdbool.h>
// --HEADERS
#include "app/window.h"
#include "app/renderer.h"
#include "game/scene.h"
#include "game/tetrimino.h"

// Entry Point
int main(int argc, char* argv[]){
    // This is our starting point
    // Creating a window
    struct PX_Window window = px_WindowCreate("BLOKOS", 512, 512);
    SDL_Renderer* renderer = px_RendererCreate(window.window);

    // Making a scene
    struct PX_Scene scene = px_SceneCreate(300, 512);

    // TESTING OBJECTS
    struct PX_Tetrimino tetrimino = px_TetriminoCreate();

    // HELPING
    bool didpress = false;

    // Game Loop
    while(window.opened){
        // Update window
        px_WindowUpdate(&window);

        // Clear screen
        px_RendererClear(renderer);

        // Game code..
        px_TetriminoUpdate(&tetrimino);
        if(tetrimino.still){
            /*
                -- THIS CODE WOULD DO THIS --
            It would "delete" the current block,
            and place it to the top of the screen.
            ======================================
            tetrimino.still = false;
            tetrimino.type += 1;
            tetrimino.y = 0;

            if(tetrimino.type >= 7) {tetrimino.type = 0;}
            */
        
            // This part of the code will spawn in a NEW block and keep the old one!
            
        }

        // Moving the tetrimino
        const Uint8* ks = SDL_GetKeyboardState(NULL);

        if(!didpress){
            if(ks[SDL_SCANCODE_LEFT]){
                // TODO: IMPLEMENT
                px_TetriminoMove(&tetrimino, -1, 0);
                didpress = true;
            }
            else if(ks[SDL_SCANCODE_RIGHT]){
                // TODO: IMPLEMENT
                px_TetriminoMove(&tetrimino, +1, 0);
                didpress = true;
            }
            else{
                // No keys, Do nothing!
            }
        }
        else if((!ks[SDL_SCANCODE_LEFT]) && (!ks[SDL_SCANCODE_RIGHT])){
            didpress = false;
        }

        // Render code
        px_TetriminoDraw(&tetrimino, &scene);
        px_SceneDraw(&scene, renderer);

        // Display screen
        px_RendererDisplay(renderer);
    }

    // Cleanup
    px_TetriminoDelete(&tetrimino);
    px_SceneDelete(&scene);
    px_RendererDelete(renderer);
    px_WindowDelete(&window);

    // Exiting the app
    return 0;
}
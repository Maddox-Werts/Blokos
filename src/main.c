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
#include "gme/scene.h"
#include "gme/tetrimino.h"
// --SCREENS
#include "scn/gameplay.h"

// Entry Point
int main(int argc, char* argv[]){
    // This is our starting point
    // Creating a window
    PX_Window window = px_WindowCreate("BLOKOS", 512, 512);
    SDL_Renderer* renderer = px_RendererCreate(window.window);

    // Making the game screen
    blk_GameStart(renderer);

    // Game Loop
    while(window.opened){
        // Update window
        px_WindowUpdate(&window);

        // Clear screen
        px_RendererClear(renderer);

        // Game code..
        blk_GameUpdate();

        // Render code
        blk_GameDraw(renderer);

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
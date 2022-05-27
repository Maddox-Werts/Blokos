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
// --BASE
#include "app/dtime.h"
// --SCREENS
#include "scn/gameplay.h"
#include "scn/mainmenu.h"

// Variables
int cscrn;
bool rtt;

// Functions
void switchscrn(){
    // Getting key state
    const Uint8* ks = SDL_GetKeyboardState(NULL);

    // If Space is pressed
    if(ks[SDL_SCANCODE_SPACE]){
        rtt = true;
    }
    else if(!(ks[SDL_SCANCODE_SPACE]) && rtt){
        cscrn = 1;
        rtt = false;
    }
}

// Entry Point
int main(int argc, char* argv[]){
    // This is our starting point
    // Creating a window
    PX_Window window = px_WindowCreate("BLOKOS", 512, 512);
    SDL_Renderer* renderer = px_RendererCreate(window.window);

    // Screen state
    cscrn = 0; rtt = false;

    // Starting the Sound System
    px_SoundStart();

    // Making the game screen
    blk_GameStart(renderer);
    blk_MMCreate(renderer);

    // Game Loop
    while(window.opened){
        // Update window
        px_WindowUpdate(&window);

        // Clear screen
        px_RendererClear(renderer);

        // Getting Delta Time
        updateTime();

        // Switching between screens
        switch(cscrn){
        case 0:
            // Game code..
            blk_MMUpdate();
            switchscrn();
            // Render code..
            blk_MMDraw(renderer);
            // End screen
            break;
        case 1:
            // Game code..
            blk_GameUpdate();
            // Render code..
            blk_GameDraw(renderer);
            // End screen
            break;
        }
        
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
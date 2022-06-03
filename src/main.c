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
#include "app/prefs.h"
#include "app/saves.h"
// --SCREENS
#include "scn/gameplay.h"
#include "scn/mainmenu.h"
#include "scn/splash.h"

// Variables
int cscrn;
bool rtt;

// Functions
void switchscrn(){
    // Getting key state
    const Uint8* ks = SDL_GetKeyboardState(NULL);

    // If Space is pressed
    if(ks[SDL_SCANCODE_SPACE] && px_mcanstart){
        rtt = true;
    }
    else if(!(ks[SDL_SCANCODE_SPACE]) && rtt){
        if(cscrn == 0) { blk_MMClean(); }
        cscrn += 1;
        rtt = false;
    }
}

// Entry Point
int main(int argc, char* argv[]){
    // This is our starting point
    // Prefrences
    PX_PrefrenceResult prefs = px_ReadPrefs();

    // Loading save game
    PX_SaveGame saveGame = px_saveRead("res/saves/save.conf");

    // Creating a window
    PX_Window window = px_WindowCreate("BLOKOS", prefs.width, prefs.height);
    SDL_Renderer* renderer = px_RendererCreate(window.window);

    // Screen state
    cscrn = -1; rtt = false;

    // Starting the Sound System
    px_SoundStart();

    // Making the game screen
    px_SSstart(renderer, window.width, window.height);
    blk_GameStart(renderer, &saveGame);
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
        case -1:
            // Game code..
            px_SSupdate();
            if(px_ssready) {cscrn = 0; px_SSclean();}
            // Render code..
            px_SSdraw(renderer, window.width, window.height);
            

            break;

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
            blk_GameUpdate(&saveGame);
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
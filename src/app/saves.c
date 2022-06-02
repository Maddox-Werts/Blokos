// Files
// --SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// --HEADER
#include "saves.h"

// Functions
PX_SaveGame px_saveRead(const char* fileName){
    // Holder
    PX_SaveGame saveGame;

    // Variables
    FILE* savefile;
    char line[512];

    printf("Reading save from: \n%s\n", fileName);
    
    // Loading from file
    savefile = fopen(fileName, "r");

    // Was the file opened?
    if(savefile == NULL){
        printf("Failed to open %s.\n", savefile);
    }
    else{
        printf("Successfully read.\n");
    }

    // Loading each line
    while(fgets(line, 512, savefile) != NULL){
        // Checking if it's a comment
        if(!(line[0] == '#')){
            // Getting the following arguments
            char* saveargs = (char*)malloc(16 * sizeof(int));

            // Split the line
            strcpy(saveargs, strtok(line, "="));

            // Temporary Variables
            char* savename;
            char* savevalue;

            // What are our arguments?
            while(saveargs != NULL){
                // What was the name
                if(savename == NULL){
                    savename = saveargs;
                }
                else{
                    savevalue = saveargs;
                }

                // Next argument
                saveargs = strtok(NULL, "=");
            }

            // What was the name?
            if(strcmp(savename, "high_score") == 0){
                saveGame.high_score = atoi(savevalue);
            }
            if(strcmp(savename, "time_alive") == 0){
                saveGame.time_alive = atoi(savevalue);
            }
        }
    }

    // Cleanup
    fclose(savefile);

    // Returning
    return saveGame;
}
void px_saveWrite(const char* filename, const char* value){
    
}
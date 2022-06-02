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
        printf("Failed to open %s.\n", fileName);
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
void px_saveWrite(const char* filename, const char* name, const char* value){
    // What's the path?
    char* path = (char*)malloc(5 * sizeof(int));
    strcpy(path, "res/saves/");
    strcat(path, filename);

    char* tpath = (char*)malloc(5 * sizeof(int));
    strcpy(tpath, path);
    strcat(tpath, ".tmp");

    // Getting the file
    FILE* savefile = fopen(path, "r");
    FILE* newfile = fopen(tpath, "w");

    // Variables
    char line[512];

    // For each of the lines
    while(fgets(line, 512, savefile) != NULL){
        // Is the line a comment?
        if(line[0] != '#'){
            // Check the arguments
            char* saveargs = (char*)malloc(4 * sizeof(int));
            strcpy(saveargs, strtok(line, "="));

            // Is this what we want?
            // Writing!
            char* result = (char*)malloc(4 * sizeof(int));

            strcpy(result, saveargs);
            strcat(result, "=");
            if(strcmp(saveargs, name)){
                strcat(result, value);
            }
            else{
                strcpy(saveargs, strtok(NULL, "="));
                strcat(result, saveargs);
            }

            // Override line
            fputs(result, newfile);
            fputc('\n', newfile);

            // Cleanup
            free(result);

            // Cleanup
            free(saveargs);
        }
        else{
            fputs(line, newfile);
        }
    }

    // Closing files
    fclose(savefile);
    fclose(newfile);

    // Remove the original
    remove(path);

    // Override
    rename(tpath, path);

    return;
}
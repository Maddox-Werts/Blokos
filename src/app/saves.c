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
            //char* saveargs = (char*)malloc(4 * sizeof(int));
            char* saveargs;

            // Split the line
            //strcpy(saveargs, line);
            saveargs = strtok(line, "=");

            // Temporary Variables
            char* savename;
            char* savevalue;

            // What are our arguments?
            savename = saveargs;

            saveargs = strtok(NULL, "=");

            savevalue = saveargs;

            printf("Loaded info:\n  Name: %s\n  Value: %s\n\n", savename, savevalue);

            // What was the name?
            if(strcmp(savename, "high_score") == 0){
                saveGame.high_score = atoi(savevalue);
                printf("Saved high score as: %i\n", saveGame.high_score);
            }
            if(strcmp(savename, "time_alive") == 0){
                saveGame.time_alive = atoi(savevalue);
                printf("Saved time alive as: %i\n", saveGame.time_alive);
            }
        }
    }

    // Cleanup
    fclose(savefile);

    // Returning
    return saveGame;
}
void px_saveWrite(const char* filename, const char* name, const char* value){
    // DEBUG
    printf("Writing to saves..\n");

    // What's the path?
    char* path = (char*)malloc(5 * sizeof(int));
    strcpy(path, "res/saves/");
    strcat(path, filename);

    char* tpath = (char*)malloc(5 * sizeof(int));
    strcpy(tpath, path);
    strcat(tpath, ".tmp");

    printf("Paths: %s, %s\n", path, tpath);

    // DEBUG
    printf("Got both save paths..\n");

    // Getting the file
    FILE* savefile = fopen(path, "r");
    FILE* newfile = fopen(tpath, "w");

    // DEBUG
    printf("Loaded both files.\nOG: %i\n NEW: %i\n", (int)(savefile == NULL), (int)(newfile == NULL));

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
            if(strcmp(saveargs, name) == 0){
                strcat(result, value);
            }
            else{
                strcpy(result, line);
                strcat(result, "=");
                strcat(result, strtok(NULL, "\n"));
            }

            printf("Result: %s\n", result);

            // Override line
            fputs(result, newfile);
            fputc('\n', newfile);

            // Cleanup
            free(result);

            // Cleanup
            free(saveargs);
        }
        else{
            // Write to file
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
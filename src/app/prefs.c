// Files
// --SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// --HEADERS
#include "prefs.h"

// Functions
PX_PrefrenceResult px_ReadPrefs(){
    // Variables
    PX_PrefrenceResult holder;

    FILE* file;
    char line[512];

    // Loading the file
    file = fopen("res/prefs.conf", "r");

    // Was the file loaded 
    if(file == NULL){
        printf("FAILED TO OPEN PREFS FILE!\n");
    }

    // Reading contents
    while(fgets(line, 512, file) != NULL){
        if(line[0] == '#'){                 // This is a comment
            
        }
        else{
            // Variables
            char* args = (char*)malloc(3 * sizeof(int));

            // Getting stuff
            strcpy(args, strtok(line, "="));

            // Holders
            char* name;
            char* value;
            int time = 0;

            // What was the thing?
            while(args != NULL){
                if(time == 0){
                    name = args;
                }
                else{
                    value = args;
                }

                args = strtok(NULL, "=");
                time += 1;
            }

            if(strcmp(name, "width") == 0){
                holder.width = atoi(value);
            }
            else if(strcmp(name, "height") == 0){
                holder.height = atoi(value);
            }

            // Clean
            free(args);
        }
    }

    // Cleanup
    fclose(file);

    // return
    return holder;
}
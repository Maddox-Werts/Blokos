// Define once
#ifndef H_SAVES
#define H_SAVES

// Files
// --SYSTEM
#include <stdio.h>
// --HEADERS

// Structures
typedef struct PX_SaveGame{
    int high_score;
    int time_alive;
} PX_SaveGame;

// Functions
PX_SaveGame px_saveRead(const char* fileName);
void px_saveWrite(const char* filename, const char* value);

// End definition
#endif
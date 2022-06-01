// Define once
#ifndef H_PREFS
#define H_PREFS

// Files
// --SYSTEM
// --HEADERS

// Structures
typedef struct PX_PrefrenceResult{
    int width, height;
} PX_PrefrenceResult;

// Functions
PX_PrefrenceResult px_ReadPrefs();

// End definition
#endif
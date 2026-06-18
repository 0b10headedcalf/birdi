#include "../lib/rngs/b_rand.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <threads.h>

//raylib stuff
#include "raylib.h"


typedef struct userOptions{
    int screenWidth;
    int screenHeight;
    int targetFPS;
    char* windowTitle;
}userOptions;

typedef enum GameScreen{
    MENU = 0,
    SETUP,
    GAME
}GameScreen;

int main(void) {
    userOptions defaultOptions = {800,600,60,"Window"};
    

    InitWindow(defaultOptions.screenWidth, defaultOptions.screenHeight, defaultOptions.windowTitle);
    
    SetTargetFPS(defaultOptions.targetFPS);
    
    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(GRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

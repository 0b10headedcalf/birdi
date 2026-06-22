#include "../lib/rngs/b_rand.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <threads.h>

//raylib stuff
#include "raylib.h"
// #include "reasings.h"
// #define RAYGUI_IMPLEMENTATION
// #include "raygui.h"


struct splashProps
{
    bool splashSkippedOrCompleted;
    int splashAnimFrames;
}splashProps;

struct WINDOWOPTIONS
{
    int screenWidth;
    int screenHeight;
    int targetFPS;
    char* windowTitle;
}WINDOWOPTIONS={800,600,60,"Birdi"};

struct menuController{}menuController={};
    
enum GameScreen
{
        SPLASH = 0,
        MENU,
        SETUP,
        GAME
};


int main(void) {

    
    InitWindow(WINDOWOPTIONS.screenWidth, WINDOWOPTIONS.screenHeight, WINDOWOPTIONS.windowTitle);
 
    
    enum GameScreen currentScreen = 0;

    bool exitWindowRequested = false;
    bool exitWindow = false;

    SetExitKey(KEY_NULL);
    SetTargetFPS(WINDOWOPTIONS.targetFPS);

    while (!exitWindow) 
    {
        if(WindowShouldClose()) exitWindowRequested = true;

        if(exitWindowRequested){
            if(IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        
        switch (currentScreen) 
        {
            case SPLASH:
                {
                if (splashProps.splashSkippedOrCompleted == true) 
                    {
                        currentScreen = 1;
                    }
                }break;
            case MENU:
                {

                }break;
            case SETUP:
                {

                }break;
            case GAME:
                {

                }break;
            default:
                break;
        }

        BeginDrawing();
        //Draw loop
            ClearBackground(GRAY);
            if(exitWindowRequested){
                DrawRectangle(0, 100, WINDOWOPTIONS.screenWidth, 200, BLACK);
                DrawText("Exit program? [Y/N]", 40, 180, 30, WHITE);
            }
                switch (currentScreen) 
                {
                    case SPLASH:
                        {
                        if (splashProps.splashSkippedOrCompleted == true) 
                            {
                                currentScreen = 1;
                            }
                        }break;
                    case MENU:
                        {

                        }break;
                    case SETUP:
                        {

                        }break;
                    case GAME:
                        {

                        }break;
                    default:
                        break;
                }

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}

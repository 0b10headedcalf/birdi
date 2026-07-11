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
}WINDOWOPTIONS={1920,1080,60,"Birdi"};

struct menuController{

}menuController={

};
    
enum GameScreen{
        SPLASH = 0,
        MENU,
        OPTIONS,
        GAME
}GameScreen;

void SwapScreens(enum GameScreen* p_gscreen){
    int CURRENT = *p_gscreen;
    printf("\nCurrent Screen State: %d", CURRENT);
}


int main(void) {

    
    InitWindow(WINDOWOPTIONS.screenWidth, WINDOWOPTIONS.screenHeight, WINDOWOPTIONS.windowTitle);
    SetExitKey(KEY_NULL);
    SetTargetFPS(WINDOWOPTIONS.targetFPS);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    float deltaTime = 0.0f;
    float timeCounter = 0.0f;
    float FPSCounter = 0.0f;

    enum GameScreen currentScreen = 0;
    enum GameScreen* p_gscreen = &currentScreen;

    
    while (!exitWindow)
    {
        if(WindowShouldClose()) exitWindowRequested = true;

        if(exitWindowRequested){
            if(IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }


        
        SwapScreens(p_gscreen);
        switch (currentScreen) 
        {
            case SPLASH:
                {
                    if(IsKeyPressed(KEY_SPACE)){
                        splashProps.splashSkippedOrCompleted = true;
                    }
                if (splashProps.splashSkippedOrCompleted == true) 
                    {
                        currentScreen = 1;
                    }
                }break;
            case MENU:
                {

                }break;
            case OPTIONS:
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
            if (deltaTime!=0){
                DrawText(TextFormat("FPS: %i",1.0f/deltaTime), GetScreenWidth() - 220, 10, 20, GREEN);

            }
            if(exitWindowRequested){
                DrawRectangle(0, 100, WINDOWOPTIONS.screenWidth, 200, BLACK);
                DrawText("Exit? [Y/N]", 40, 180, 30, WHITE);
            }
                switch (currentScreen) 
                {
                    case SPLASH:
                        {
                            DrawText("Splash", GetScreenWidth () / 2, GetScreenHeight() / 2, 36, RED);
                        }break;
                    case MENU:
                        {
                            DrawText("Menu", GetScreenWidth() / 2, GetScreenHeight() / 2, 36, BLUE);

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

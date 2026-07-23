#include <raylib.h>
#include <raymath.h>

#include "../lib/b_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct
{
    int width;
    int height;
    float currentFPS;
    b_String title;
}Settings = {800,600,60,{"Birdi",5}};

int main(int argc, char *argv[])
{
    InitWindow(Settings.width, Settings.height, Settings.title.data);
    SetTargetFPS(Settings.currentFPS);

    while (!WindowShouldClose())       
    {
        //render loop
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),Settings.currentFPS);
        DrawText(fpsText,10,10,20,GREEN);

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}

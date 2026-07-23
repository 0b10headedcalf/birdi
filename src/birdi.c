#include <raylib.h>
#include <raymath.h>

#include "../lib/b_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define WIDTH  800
#define HEIGHT 600

int main(int argc, char *argv[])
{
    InitWindow(WIDTH, HEIGHT, "birdi");
    SetTargetFPS(60);

    while (!WindowShouldClose())   // true on window-close or ESC
    {
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   // your old 0.2,0.2,0.3


        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}

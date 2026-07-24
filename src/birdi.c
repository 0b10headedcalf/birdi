#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#include "../lib/b_core.h"

typedef struct Settings
{
    int width;
    int height;
    float currentFPS;
    char* title;
}Settings;

enum ARGS{
    STANDALONE,
};

void print_help(void){
    puts("Simulation library and included loader for creative coding and simulation of natural systems. Hoping to extend this later! Pass in --standalone to run the binary without an example or loaded simulation file.");
    puts("Usage: birdi.bin [simfile/example]");
}

void LoadExample(FILE* example){
}

int main(int argc, char *argv[])
{
    uint8_t opt;
    enum{STANDALONE} mode = STANDALONE;
    while(opt = getopt(argc,argv,"")){
        
    }
    if(argc <= 1){
        fprintf(stderr,"Please denote a command or run with 'standalone' flag");
        return EXIT_FAILURE;
    }

    static Settings global_defaults = {800,600,60,"Birdi\0"};
    Settings*  Settings = &global_defaults;

    InitWindow(Settings->width, Settings->height, Settings->title);
    SetTargetFPS(Settings->currentFPS);

    while (!WindowShouldClose())       
    {
        //render loop
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),Settings->currentFPS);
        DrawText(fpsText,10,10,20,GREEN);

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}

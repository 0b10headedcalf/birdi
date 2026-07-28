#include <raylib.h>
#include <raymath.h>
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "../lib/b_core.h"

typedef struct Settings
{
    int width;
    int height;
    float currentFPS;
    char* title;
}Settings;


enum{STANDALONE,LOAD} mode;

void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems. Hoping to extend this later!\nPass in -s to run the binary without an example or loaded simulation file.");
}


void _isStandalone(Settings* Settings){
        //render loop
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),Settings->currentFPS);
        DrawText(fpsText,10,10,20,GREEN);
        EndDrawing();
}

int main(int argc, char *argv[])
{
    if(argc <= 1){
        fprintf(stderr,"Please denote a command");
        return EXIT_FAILURE;
    }

    
    int8_t opt;
    
    while((opt = getopt(argc,argv,"shl:")) != -1){
        switch(opt){
            case 's':
                puts("Standalone mode");
                mode = STANDALONE;
                break;
            case 'l':
                puts("Example mode");
                mode = LOAD;
                break;
            case 'h':
                print_help();
                exit(EXIT_FAILURE);
                break;
            default: 
                puts("\nUsage: birdi.bin -l [file/example]");
                exit(EXIT_FAILURE);
        }
        
    }

    //setup
    static Settings global_defaults = {800,600,60,"Birdi\0"};
    Settings*  Settings = &global_defaults;
    InitWindow(Settings->width, Settings->height, Settings->title);
    SetTargetFPS(Settings->currentFPS);
    while (!WindowShouldClose())       
    {
        if(mode == STANDALONE){
            _isStandalone(Settings);
        }
        else{
            //TODO: dynamic library loading
            void* handle = dlopen(argv[2],RTLD_NOW);
            if (!handle) {
               fprintf(stderr, "%s\n", dlerror());
               exit(EXIT_FAILURE);
           }
    }   

    CloseWindow();
    return EXIT_SUCCESS;
}
}


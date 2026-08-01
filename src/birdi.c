#include <raylib.h>
#include <raymath.h>
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/b_core.h"


enum
{
    STANDALONE,
    LOAD,
    _NULL
}MODE = _NULL;

typedef enum {
    ST_SPLASH,
    ST_LOADMENU,
    ST_PRESETS,
    ST_LOADED
}State;

struct GameManager_t{
    State next_state;
};

void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems. Hoping to extend this later!\nPass in -s to run the binary without an example or loaded simulation file.");
}

void play_splash(){
    //TODO implement splash screen
    return;
}



void _standalone(Settings* Settings,struct GameManager_t* state){
        //render loop
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),Settings->currentFPS);
        DrawText(fpsText,10,10,20,GREEN);
        EndDrawing();
}

int _loadEx(const char* example, Settings* settings){
    void* handle = dlopen(example, RTLD_NOW);
    if (handle == NULL){
        fprintf(stderr,"Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    //function pointer for running the example
    int (*run)(Settings* settings) = dlsym(handle,"run");
    if(run == NULL){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    run(settings);

    dlclose(handle);
    return EXIT_SUCCESS;
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
                MODE = STANDALONE;
                break;
            case 'l':
                puts("Example mode");
                MODE = LOAD;
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
    Settings global_defaults = {1024,768,60,"Birdi\0"}; 
    Settings*  Settings = &global_defaults;
    struct GameManager_t _state;
    struct GameManager_t* p_state = &_state;
    InitWindow(Settings->width, Settings->height, Settings->title);
    SetTargetFPS(Settings->currentFPS);
    
    //load shared lib
    switch(MODE){
        case STANDALONE:
            while(!WindowShouldClose()){
                _standalone(Settings, p_state);
            }
            break;
        case LOAD:
            printf("Loading object: %s\n", argv[2]);
            while (!WindowShouldClose()){
                _loadEx(argv[2], Settings);
            }
            break;
        case _NULL:
            fprintf(stderr,"incorrect usage\n");
            exit(EXIT_FAILURE);
    }
    CloseWindow();
    return EXIT_SUCCESS;
    }


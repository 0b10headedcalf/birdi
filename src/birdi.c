#include <raylib.h>
#include <raymath.h>
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/b_core.h"


typedef enum
{
    LOAD,
    _NULL
}MODE;

typedef enum state_enum{
    ST_SPLASH = 0,
    ST_LOADMENU,
    ST_PRESETS,
    ST_LOADED
}state_enum;


void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems.\n");
}

void play_splash(){
    //TODO implement splash screen
    return;
}


//this ended up being mostly useless
// void _standalone(Settings Settings, struct GameManager_t* state){
//         //render loop
//         BeginDrawing();
//         ClearBackground((Color){ 51, 51, 77, 255 });   
//
//         //FPS counter
//         const char* fpsText = 0;
//         fpsText = TextFormat("FPS: %i",GetFPS(),Settings.currentFPS);
//         DrawText(fpsText,10,10,20,GREEN);
//         EndDrawing();
// }

int _loadEx(const char* example){
    void* handle = dlopen(example, RTLD_LAZY);
    if (handle == NULL){
        fprintf(stderr,"Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    //function pointer for running
    int (*run)() = dlsym(handle,"run");
    if(run == NULL){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    run();

    dlclose(handle);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    MODE CURRENTMODE = _NULL;

    if(argc <= 1){
        Settings* global_defaults = &(Settings) {
            1024,
            768,
            60,
            "Birdi"
        };
        InitWindow(global_defaults->width, global_defaults->height, global_defaults->title);
        SetTargetFPS(global_defaults->currentFPS);
        while(!WindowShouldClose()){
        // state_enum_t state_enum = RUNNING;
        // struct GameManager_t GameManager;
        // GameManager.state_enum = &state_enum;
        // if(IsKeyPressed(KEY_P) && GameManager.state_enum != PAUSED) {
        //     *GameManager.state_enum = PAUSED;
        // }
        // else{
        //     *GameManager.state_enum = RUNNING;
        // }
        // while(!init){
        BeginDrawing();
        ClearBackground(BLACK);   
            //FPS counter
            const char* fpsText = 0;
            fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
            DrawText(fpsText,10,10,20,GREEN);
            EndDrawing();
            }
        CloseWindow();
    }

    int8_t opt;
    
    while((opt = getopt(argc,argv,"shl:")) != -1){
        switch(opt){
            case 'l':
                puts("Example mode");
                CURRENTMODE = LOAD;
                break;
            case 'h':
                print_help();
                exit(EXIT_FAILURE);
                break;
            default: 
                puts("\n Invalid command!");
                exit(EXIT_FAILURE);
        }
        
    }
    //load shared lib
    switch(CURRENTMODE){
        case LOAD:
            printf("Loading object: %s\n", argv[2]);
            _loadEx(argv[2]);
            break;
        case _NULL:
            fprintf(stderr,"incorrect usage\n");
            exit(EXIT_FAILURE);
        }
    return EXIT_SUCCESS;
    }


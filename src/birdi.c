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
    STANDALONE,
    LOAD,
    _NULL
}MODE;

typedef enum state_enum_t{
    ST_SPLASH = 0,
    ST_LOADMENU,
    ST_PRESETS,
    ST_LOADED
}state_enum;

typedef struct GameManager_t{
    state_enum state_enum;
}GameManager;

void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems. Hoping to extend this later!\nPass in -s to run the binary without an example or loaded simulation file.");
}

void play_splash(){
    //TODO implement splash screen
    return;
}



void _standalone(Settings Settings, struct GameManager_t* state){
        //render loop
        BeginDrawing();
        ClearBackground((Color){ 51, 51, 77, 255 });   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),Settings.currentFPS);
        DrawText(fpsText,10,10,20,GREEN);
        EndDrawing();
}

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
    GameManager _state;
    GameManager* p_state = malloc(sizeof(_state));
    
    printf("State is at: %p with size of: %ld\n", p_state,sizeof(_state));

    if(argc <= 1){
        fprintf(stderr,"Please denote a command");
        return EXIT_FAILURE;
    }

    
    int8_t opt;
    
    while((opt = getopt(argc,argv,"shl:")) != -1){
        switch(opt){
            case 's':
                puts("Standalone mode");
                CURRENTMODE = STANDALONE;
                break;
            case 'l':
                puts("Example mode");
                CURRENTMODE = LOAD;
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
    
    //load shared lib
    switch(CURRENTMODE){
        case STANDALONE:
            Settings defaults = {1024,768,60,"Birdi\0"}; 
            p_state->state_enum = ST_LOADED;
            InitWindow(defaults.width, defaults.height, defaults.title);
            SetTargetFPS(defaults.currentFPS);
            while(!WindowShouldClose()){
                _standalone(defaults, p_state);
            }
            CloseWindow();
            break;
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


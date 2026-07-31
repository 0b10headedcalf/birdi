#include <raylib.h>
#include <raymath.h>
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "../lib/b_core.h"


enum
{
    STANDALONE,
    LOAD,
    _NULL
}mode = _NULL;

void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems. Hoping to extend this later!\nPass in -s to run the binary without an example or loaded simulation file.");
}


void _standalone(Settings* Settings){
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
    typedef int (*func)(Settings* settings);
    void* handle = dlopen(example, RTLD_LAZY);
    if (handle == NULL){
        fprintf(stderr,"Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    func run_example = dlsym(handle,"run"); 
    if(run_example == NULL){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    run_example(settings);

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
    
    //load shared lib
    switch(mode){
        case STANDALONE:
            while(!WindowShouldClose()){
                _standalone(Settings);
            }
            break;
        case LOAD:
            printf("Loading object: %s\n", argv[2]);
            while (!WindowShouldClose()){
                _loadEx(argv[2], Settings);
            }
            break;
        case _NULL:
            exit(EXIT_FAILURE);
    }
    CloseWindow();
    return EXIT_SUCCESS;
    }


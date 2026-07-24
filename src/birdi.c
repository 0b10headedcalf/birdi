#include <raylib.h>
#include <raymath.h>
// #include <rlgl.h>
#include <stdio.h>

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
    puts("Included loader for creative coding and simulation of natural systems. Hoping to extend this later!\nPass in -s to run the binary without an example or loaded simulation file.");
}

void LoadExample(FILE* example){
}

int main(int argc, char *argv[])
{
    if(argc <= 1){
        fprintf(stderr,"Please denote a command");
        return EXIT_FAILURE;
    }

    // FILE* _load;
    
    int opt;
    
    enum{STANDALONE,LOAD} mode;
    
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
                break;
            default: 
                puts("\nUsage: birdi.bin [opt] [file/example]");
                exit(EXIT_FAILURE);
        }
        
    }

    //setup
    if(mode == STANDALONE){
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
    }
    else if(mode == LOAD){
        // _load = fopen(argv[2], "r");
        // char data[50];
        // while(fgets(data,50,_load) != NULL){
        //     printf("%s",data);
        // }
        // fclose(_load);
    }
    return EXIT_SUCCESS;
}

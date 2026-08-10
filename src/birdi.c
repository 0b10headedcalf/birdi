#include <raylib.h>
#include <stdint.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/b_core.h"


#define MAX_FILEPATH_SIZE 1024
#define FILE_FILTER "DIRS*;.so;.c"


enum MODE
{
    LOAD,
    _NULL
};

typedef enum state_enum{
    ST_SPLASH = 0,
    ST_MENU,
    ST_DIR,
    ST_OPTIONS,
    ST_LOADED
}state_enum;

static bool SPLASH_DONE = false;

void print_help(void){

    puts("Included loader for creative coding and simulation of natural systems.\n");
}

void play_splash(){
    //TODO implement splash screen
    DrawText("SPLASH_PLACEHOLDER", 20, 20, 40, BLACK);
    if(IsKeyPressed(KEY_ENTER)){
        SPLASH_DONE = true;
    }
    return;
}


//this ended up being mostly unused
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
    enum MODE CURRENTMODE = _NULL;

    if(argc <= 1){
        Settings* global_defaults = &(Settings) {
            1280,
            720,
            60,
            "Birdi"
        };

        //menu state
        state_enum STATE = ST_SPLASH;

        //fd
        char directory[MAX_FILEPATH_SIZE] = {0};
        strcpy(directory,GetWorkingDirectory());

        FilePathList files = LoadDirectoryFilesEx(directory, FILE_FILTER, false);
        int listScrollIndex = 0;
        int listItemActive = -1;
        int listItemFocused = -1;

        //gui vars
        int btn = 0;

        //init
        InitWindow(global_defaults->width, global_defaults->height, global_defaults->title);
        Font c_font = LoadFontEx("assets/fonts/geist-pixel-latin-400-normal.ttf",128,0,250);
        SetTextLineSpacing(16);
        static bool fpsCounter = false;

        SetTargetFPS(global_defaults->currentFPS);
        while(!WindowShouldClose()){
            if(btn){
                TextCopy(directory, GetPrevDirectoryPath(directory));
                UnloadDirectoryFiles(files);
                files = LoadDirectoryFilesEx(directory, FILE_FILTER, false);
                int listScrollIndex = 0;
                int listItemActive = -1;
                int listItemFocused = -1;
            }
            if(listItemActive >= 0 && (listItemActive < (int)files.count) && DirectoryExists(files.paths[listItemActive])){
                TextCopy(directory,files.paths[listItemActive]);
                UnloadDirectoryFiles(files);
                files = LoadDirectoryFilesEx(directory, FILE_FILTER, false);
                int listScrollIndex = 0;
                int listItemActive = -1;
                int listItemFocused = -1;
            }

            //primary logic
            switch(STATE){
                case ST_SPLASH:
                    {
                        if(SPLASH_DONE == true){
                            STATE = ST_MENU;
                        }
                    }
                    break;
                case ST_MENU:
                    {
                        if(IsKeyPressed(KEY_ENTER)) STATE = ST_DIR;
                    }
                    break;
                case ST_DIR:
                    {
                        if(IsKeyPressed(KEY_ENTER)) STATE = ST_LOADED;

                    }
                    break;
                case ST_OPTIONS:
                    {

                    }
                    break;
                case ST_LOADED:
                    {
                        if(IsKeyPressed(KEY_ENTER)) CloseWindow();
                    }
                    break;
                default:
                    break;
                }
            

            //rendering loop
            BeginDrawing();
                ClearBackground(RAYWHITE);
                switch(STATE){
                    case ST_SPLASH:
                        {
                            play_splash();
                        }
                        break;
                    case ST_MENU:
                        {
                            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);   
                            //FPS counter
                            if(fpsCounter){
                                const char* fpsText = 0;
                                fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
                                DrawText(fpsText,10,10,20,GREEN);
                            }
                            //TODO implement splash screen
                            //
                            DrawTextEx(c_font,"MENU NEW FONT",(Vector2){50,50},64,2,WHITE);

                        }
                        break;
                    case ST_DIR:
                        {
                            //FPS counter
                            if(fpsCounter){
                                const char* fpsText = 0;
                                fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
                                DrawText(fpsText,10,10,20,GREEN);
                            }
                            btn = GuiButton((Rectangle){40.0f,10.0f,48,28}, "<");
                            GuiLabel((Rectangle){ 40 + 48 + 10, 10, 700, 28 }, directory);
                            // GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetFont().baseSize);

                            
                            GuiListViewEx((Rectangle){ 0, 50, (float)GetScreenWidth(), (float)GetScreenHeight() - 50 },
                                files.paths, files.count, &listScrollIndex, &listItemActive, &listItemFocused);
                        }
                        break;
                    case ST_OPTIONS:
                        {
                            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);   
                            //FPS counter
                            if(fpsCounter){
                                const char* fpsText = 0;
                                fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
                                DrawText(fpsText,10,10,20,GREEN);
                            }

                        }
                        break;
                    case ST_LOADED:
                        {
                            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);   
                            //FPS counter
                            if(fpsCounter){
                                const char* fpsText = 0;
                                fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
                                DrawText(fpsText,10,10,20,GREEN);
                            }
                            //TODO implement splash screen
                            DrawText("LOADED", 20, 20, 40, WHITE);

                        }
                        break;
                    default:
                        break;
                    }
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
            exit(EXIT_SUCCESS);
        }
    return EXIT_SUCCESS;
    }


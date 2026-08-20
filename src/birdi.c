#include <raylib.h>
#include <stdint.h>
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
// #include <rlgl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#define BIRDI_IMPL
#include "../lib/birdi.h"
//macros
#define MAX_FILE_PATH_LEN 1024
#define FONT_PRESET "assets/fonts/geist-pixel-latin-400-normal.ttf"



typedef enum
{
    STANDALONE=0,
    LOAD,
}MODE;

typedef enum{
    ST_SPLASH = 0,
    ST_MENU,
    ST_DIR,
    ST_OPTIONS,
    ST_LOADED
}Main_App_State;

static bool SPLASH_DONE = false;

void print_help(){
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

int _loadEx(const char* example, Settings* global_defaults, bool loader){
    void* handle = dlopen(example, RTLD_LAZY);
    if (handle == NULL){
        fprintf(stderr,"Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    //function pointer for running
    int (*run)(bool,Settings*) = dlsym(handle,"run");
    if(run == NULL){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    run(loader,global_defaults);

    dlclose(handle);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    Settings* global_defaults = &(Settings) {
        GetScreenWidth(),
        GetScreenHeight(),
        60,
        "Birdi"
    };
    MODE _MODE = -1;
    int opt;

    while((opt = getopt(argc,argv,"hl")) != -1){
        switch(opt){
            case 'l':
                puts("Loading example...");
                _MODE = LOAD;
                break;
            case 'h':
                print_help();
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }

    }
    //if an example is loaded from the main binary rather than using -l in the cli
    if(_MODE == LOAD){
        printf("Loading object: %s\n", argv[2]);
        _loadEx(argv[2],global_defaults,false);
        }
    //checking if the binary is run directly
    if(argc <= 1){
        //menu state
        Main_App_State main_state = ST_SPLASH;

        //fd
        char directory[MAX_FILE_PATH_LEN] = {0};
        strncpy(directory, GetWorkingDirectory(), strlen(GetWorkingDirectory()));
        FilePathList files = LoadDirectoryFiles(directory);
        int listScrollIndex = 0;
        int listItemActive = -1;
        int listItemFocused = -1;

        //gui stuff
        int dir_back_button = 0;
        
        //init
        SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
        InitWindow(global_defaults->width, global_defaults->height, global_defaults->title);
        Font c_font = LoadFontEx(FONT_PRESET,128,0,250);
        // SetTextLineSpacing(16);
        volatile bool fpsCounter = false;

        SetTargetFPS(global_defaults->currentFPS);
 
        while(!WindowShouldClose()){
            //primary logic
            switch(main_state){
                case ST_SPLASH:
                    {
                        if(SPLASH_DONE == true){
                            main_state = ST_MENU;
                        }
                    }
                    break;
                case ST_MENU:
                    {
                        if(IsKeyPressed(KEY_ENTER)) main_state = ST_DIR;
                    }
                    break;
                case ST_DIR:
                    {
                        if(dir_back_button){
                            TextCopy(directory, GetPrevDirectoryPath(directory));
                            UnloadDirectoryFiles(files);
                            files = LoadDirectoryFiles(directory);
                            // listScrollIndex = 0;
                            // listItemActive = -1;
                            // listItemFocused = -1;
                        }
                        if(listItemActive >= 0 && (listItemActive < (int)files.count) && DirectoryExists(files.paths[listItemActive])){
                            TextCopy(directory,files.paths[listItemActive]);
                            UnloadDirectoryFiles(files);
                            files = LoadDirectoryFiles(directory);
                            // listScrollIndex = 0;
                            // listItemActive = -1;
                            // listItemFocused = -1;
                        }
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
                switch(main_state){
                    case ST_SPLASH:
                        {
                            play_splash();
                        }
                        break;
                    case ST_MENU:
                        {
                            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);   
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
                            dir_back_button = GuiButton((Rectangle){40.0f,10.0f,48,28}, "<");
                            GuiLabel((Rectangle){ 40 + 48 + 10, 10, 700, 28 }, directory);
                            GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetFont().baseSize);

                            
                            GuiListViewEx((Rectangle){ 0, 50, (float)GetScreenWidth(), (float)GetScreenHeight() - 50 },
                                files.paths, files.count, &listScrollIndex, &listItemActive, &listItemFocused);
                        }
                        break;
                    case ST_OPTIONS:
                        {
                            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);   
                            //FPS counter

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
    return EXIT_SUCCESS;
    }


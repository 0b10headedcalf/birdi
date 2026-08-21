#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
#define BIRDI_IMPLEMENTATION
#include "../lib/birdi.h"
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_FILE_PATH_LEN 1024
#define MASCOT_PATH "assets/images/pip.gif"
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
}MenuState;

typedef struct{
    bool SPLASH_DONE;
    char directory[MAX_FILE_PATH_LEN];
    int FDScrollIndex;
    int FDItemActive;
    int FDItemFocused;
}App;

typedef struct{
    int dir_back_button;
}GUI;


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
    int SWIDTH = 1024;
    int SHEIGHT = 768;
    int TARGETFPS = 60;
    const char* WINDOWTITLE = "Birdi";


    Settings* SimSettings = &(Settings) {
        SWIDTH,
        SHEIGHT,
        TARGETFPS,
        WINDOWTITLE
    };
    MODE _MODE = -1;
    int cli_opt;

    assert(_MODE != STANDALONE || _MODE != LOAD);

    while((cli_opt = getopt(argc,argv,"hl")) != -1){
        switch(cli_opt){
            case 'l':
                puts("Loading example...");
                _MODE = LOAD;
                break;
            case 'h':
                puts("Included loader for creative coding and simulation of natural systems.\nRun the binary with the -l flag to load a shared object!\nThe standalone version also includes a file browser.\nHave fun!");
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }

    }
    //if an example is loaded from the main binary rather than using -l in the cli
    if(_MODE == LOAD){
        printf("Loading object: %s\n", argv[2]);
        _loadEx(argv[2],SimSettings,false);
        }
    //checking if the binary is run directly
    if(argc <= 1){
        //menu state
        MenuState menu_state = ST_SPLASH;
        App* app_state = &(App){
            false,//splash is finished
            {0},//directory string
            0, //ScrollIndex
            -1,//ItemActive
            -1,//ItemFocused
        };
        GUI* MenuGui  = &(GUI){
            0,//back_button
        };
        //fd
        char* directory = app_state->directory;
        strncpy(directory, GetWorkingDirectory(), strlen(GetWorkingDirectory()));
        FilePathList files = LoadDirectoryFiles(directory);
        //gui stuff
        
        //init
        // SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
        InitWindow(SimSettings->width, SimSettings->height, SimSettings->title);
        Font c_font = LoadFontEx(FONT_PRESET,128,0,250);
        // SetTextLineSpacing(16);
        volatile bool fpsCounter = false;

        SetTargetFPS(SimSettings->currentFPS);
 
        while(!WindowShouldClose()){
            //primary logic
            switch(menu_state){
                case ST_SPLASH:
                    {
                        if(app_state->SPLASH_DONE == true){
                            menu_state = ST_MENU;
                        }
                    }
                    break;
                case ST_MENU:
                    {
                        if(IsKeyPressed(KEY_ENTER)) menu_state = ST_DIR;
                    }
                    break;
                case ST_DIR:
                    {
                        if(MenuGui->dir_back_button || IsKeyPressed(KEY_BACKSPACE)){
                            TextCopy(directory, GetPrevDirectoryPath(directory));
                            // UnloadDirectoryFiles(files);
                            files = LoadDirectoryFiles(directory);
                            // listScrollIndex = 0;
                            // listItemActive = -1;
                            // listItemFocused = -1;
                        }
                        if(app_state->FDItemActive >= 0 && (app_state->FDItemActive < (int)files.count) && DirectoryExists(files.paths[app_state->FDItemActive])){
                            TextCopy(directory,files.paths[app_state->FDItemActive]);
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
                switch(menu_state){
                    case ST_SPLASH:
                        {
                            DrawText("SPLASH_PLACEHOLDER", 20, 20, 40, BLACK);
                            if(IsKeyPressed(KEY_ENTER)){
                                app_state->SPLASH_DONE = true;
                            }
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
                            MenuGui->dir_back_button = GuiButton((Rectangle){40.0f,20.0f,100,50}, "< BACK");
                            GuiLabel((Rectangle){ (float)(SWIDTH/ 2.0f) - 100.0f, 10, 800, 50 }, directory);
                            GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetFont().baseSize);
                            GuiListViewEx((Rectangle){ 0, 50, (float)SWIDTH, (float)SHEIGHT - 50 },
                                files.paths, files.count, &app_state->FDScrollIndex, &app_state->FDItemActive,&app_state->FDItemFocused);
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
                                fpsText = TextFormat("FPS: %i",GetFPS(),SimSettings->currentFPS);
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


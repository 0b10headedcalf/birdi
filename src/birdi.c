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
#define MASCOT_PATH "assets/images/pip.png"
#define FONT_PRESET "assets/fonts/geist-pixel-latin-400-normal.ttf"
#define THEME "assets/themes/theme.rgs"

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
    int dir_back_button;
    char directory[MAX_FILE_PATH_LEN];
    int FDScrollIndex;
    int FDItemActive;
    int FDItemFocused;
}GUI;

typedef struct{
    GUI* GUI;
    bool SPLASH_DONE;
}App;



int _loadExCLI(const char* example, Settings* global_defaults, bool loader){
    void* handle = dlopen(example, RTLD_LAZY);
    if (handle == NULL){
        fprintf(stderr,"Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
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

    Settings DefaultSettings = {
        1280,
        720,
        60,
        "Birdi\0"
    };

    //standard defaults
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
        _loadExCLI(argv[2],&DefaultSettings,false);
        }

    if(argc <= 1){
        //gui stuff
        
        //init
        InitWindow(DefaultSettings.width, DefaultSettings.height, "Birdi");
        // SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
        Settings* SimSettings = &(Settings){
            GetScreenWidth(),
            GetScreenHeight(),
            60,
            "Birdi"
        };
        int SWIDTH = SimSettings->width;
        int SHEIGHT = SimSettings->height;
        
        GuiLoadStyle(THEME);

        SetWindowSize(SWIDTH, SHEIGHT);
        


        //menu state
        MenuState menu_state = ST_SPLASH;
        GUI* MenuGui_Init  = &(GUI){
            0,//back_button
            {0},//directory string
            0, //ScrollIndex
            0,//ItemActive
            0,//ItemFocused
        };
        App App = {MenuGui_Init,false};
        App.GUI = MenuGui_Init;
        //fd
        char* directory = App.GUI->directory;
        strncpy(directory, GetWorkingDirectory(), strlen(GetWorkingDirectory()));
        FilePathList files = LoadDirectoryFiles(directory);
        Font c_font = LoadFontEx(FONT_PRESET,128,0,250);
        Texture2D pip_tex = LoadTexture(MASCOT_PATH);
        
        //splash screen stuff
        float elapsed = 0.0f;
        float splash_alpha = 0.0f;


        static bool fpsCounter = false;

        SetTargetFPS(SimSettings->currentFPS);
 
        while(!WindowShouldClose()){
            //primary logic
            switch(menu_state){
                case ST_SPLASH:
                    {
                        if(App.SPLASH_DONE == true){
                            menu_state = ST_MENU;
                        }
                        if(IsKeyPressed(KEY_ENTER)){
                            App.SPLASH_DONE = true;
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
                ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
                switch(menu_state){
                    case ST_SPLASH:
                        {
                        DrawRectangle(0, 0, SWIDTH, SHEIGHT, BLACK);
                        enum FADE_STATES {
                            FADEIN,
                            FADEHOLD,
                            FADEOUT
                        };
                        enum FADE_STATES splash_fade = FADEIN;
                        elapsed += GetFrameTime();
                        if(elapsed < 2.0f){
                            splash_alpha = elapsed / 2.0f;
                        }
                        else if(elapsed < 4.0f){
                            splash_alpha = 1.0f;
                        }
                        else if(elapsed < 6.0f){
                            splash_alpha = 1.0f - (elapsed - 4.0f)/2.0f;
                        }
                        else {
                            splash_alpha = 0.0f;
                            App.SPLASH_DONE = true;
                        }
                        float logo_scale_factor = 6.0f;
                        const char* skip_prompt = "Press Enter to Skip\0";
                        Vector2 size = MeasureTextEx(c_font, skip_prompt, 40, 0);
                        DrawTextEx(c_font, skip_prompt, (Vector2){(SWIDTH - size.x)/2.0f,SHEIGHT - 50.0f},40.0f, 0, WHITE);
                        switch(splash_fade){
                            case FADEIN:
                        DrawTextureEx(pip_tex, (Vector2){SWIDTH/2.0f - pip_tex.width/2.0f * logo_scale_factor, SHEIGHT/2.0f - pip_tex.height/2.0f * logo_scale_factor}, 0.0f, logo_scale_factor, Fade(WHITE, splash_alpha));
                        break;
                            case FADEHOLD:
                        DrawTextureEx(pip_tex, (Vector2){SWIDTH/2.0f - pip_tex.width/2.0f * logo_scale_factor, SHEIGHT/2.0f - pip_tex.height/2.0f * logo_scale_factor}, 0.0f, logo_scale_factor, Fade(WHITE, 1.0f));
                        break;
                            case FADEOUT:
                        DrawTextureEx(pip_tex, (Vector2){SWIDTH/2.0f - pip_tex.width/2.0f * logo_scale_factor, SHEIGHT/2.0f - pip_tex.height/2.0f * logo_scale_factor}, 0.0f, logo_scale_factor, Fade(WHITE, splash_alpha));
                        break;
                            }
                        }
                        break;
                    case ST_MENU:
                        {
                            const char* title = "Birdi\0";
                            const int fontsize = 128.0f;
                            Vector2 size = MeasureTextEx(c_font, title, fontsize, 0);
                            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
                            DrawTextEx(c_font,title,(Vector2){(SWIDTH - size.x)/2.0f,fontsize},fontsize,0,BLACK);
                        }
                        break;
                    case ST_DIR:
                        {
                            MenuGui_Init->dir_back_button = GuiButton((Rectangle){40.0f,20.0f,100,50}, "< BACK");
                            GuiLabel((Rectangle){ (float)(SWIDTH/ 2.0f) - 100.0f, 10, 800, 50 }, directory);
                            GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetFont().baseSize);
                            GuiListViewEx((Rectangle){ 0, 50, (float)SWIDTH, (float)SHEIGHT - 50 },
                                files.paths, 
                                files.count, 
                                &App.GUI->FDScrollIndex, 
                                &App.GUI->FDItemActive,
                                &App.GUI->FDItemFocused);
                        if(MenuGui_Init->dir_back_button || IsKeyPressed(KEY_BACKSPACE)){
                            TextCopy(directory, GetPrevDirectoryPath(directory));
                            // UnloadDirectoryFiles(files);
                            files = LoadDirectoryFiles(directory);
                            // listScrollIndex = 0;
                            // listItemActive = -1;
                            // listItemFocused = -1;
                        }
                        if(App.GUI->FDItemActive >= 0 && (App.GUI->FDItemActive < (int)files.count) && DirectoryExists(files.paths[App.GUI->FDItemActive])){
                            TextCopy(directory,files.paths[App.GUI->FDItemActive]);
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

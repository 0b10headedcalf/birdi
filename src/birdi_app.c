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

//structs n such
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
}FD_GUI;


typedef struct{
    FD_GUI* FD_GUI;
    bool SPLASH_DONE;
}App;


//function declarations
static int _loadExCLI(const char* example, Settings* global_defaults, bool loader);

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
    int cli_opt = 0;
    // assert(_MODE != STANDALONE || _MODE != LOAD);

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
        InitWindow(GetScreenWidth(), GetScreenHeight(), "Birdi");
        // SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
        int SWIDTH = GetScreenWidth();
        int SHEIGHT = GetScreenHeight();
        int TARGETFPS = 60;
        Settings* SimSettings = &(Settings){
            SWIDTH,
            SHEIGHT,
            TARGETFPS,
            "Birdi"
        };
        SetTargetFPS(TARGETFPS);
        
        //style
        GuiLoadStyle(THEME);
        Font c_font = LoadFontEx(FONT_PRESET,128,NULL,0);
        GuiSetFont(c_font);
        //labels
        GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
        //buttons
        // SetWindowSize(SWIDTH, SHEIGHT);
        SetShapesTexture((Texture2D){0}, (Rectangle){0,0,1,1});
        //menu state
        MenuState menu_state = 0;
        FD_GUI* FDGUI_Init  = &(FD_GUI){
            0,//back_button
            {0},//directory string
            0, //ScrollIndex
            0,//ItemActive
            0,//ItemFocused
        };
        App App = {FDGUI_Init,false};
        App.FD_GUI = FDGUI_Init;

        //fd
        char* directory = App.FD_GUI->directory;
        strncpy(directory, GetWorkingDirectory(), strlen(GetWorkingDirectory()));
        FilePathList files = LoadDirectoryFiles(directory);
        Texture2D pip_tex = LoadTexture(MASCOT_PATH);
        
        //splash screen stuff
        float elapsed = 0.0f;
        float splash_alpha = 0.0f;

        //misc flags
        // static bool fpsCounter = false;
        bool exitWindow = false;
        bool exitWindowRequested = false;
        SetExitKey(KEY_NULL);

        //primary logic
        while(!exitWindow){
            if(WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)){
                exitWindowRequested = true;
            }
            if(exitWindowRequested){
                if (IsKeyPressed(KEY_Y)) exitWindow = true;
                else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
            }

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
                        ClearBackground(BLACK);
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
                            const float buttonWidth = 240.0f;
                            const float buttonHeight = 48.0f;
                            const float gap = 16.0f;
                            const float titleHeight = 48.0f;
                            const float titleGap = 32.0f;
                            const float menuHeight = titleHeight + titleGap
                                + 4 * buttonHeight + 3 * gap;
                            const float x = (SWIDTH - buttonWidth) / 2.0f;
                            const float top = (SHEIGHT - menuHeight) / 2.0f;
                            const float firstButtonY = top + titleHeight + titleGap;
                            Rectangle mm_layoutRecs[5];
                            for (int i = 0; i < 4; ++i) {
                                mm_layoutRecs[i] = (Rectangle){
                                    x, firstButtonY + i * (buttonHeight + gap),
                                    buttonWidth, buttonHeight
                                };
                            }
                            mm_layoutRecs[4] = (Rectangle){x, top, buttonWidth, titleHeight};
                            const char* title = "Birdi\0";
                            // const int fontsize = 128.0f;
                            // Vector2 size = MeasureTextEx(c_font, title, fontsize, 0);
                            // ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
                            // DrawTextEx(c_font,title,(Vector2){(SWIDTH - size.x)/2.0f,fontsize},fontsize,0,BLACK);
                            if (GuiButton(mm_layoutRecs[0], "SELECT")) menu_state=ST_LOADED; 
                            if (GuiButton(mm_layoutRecs[1], "LOAD")) menu_state=ST_DIR; 
                            if (GuiButton(mm_layoutRecs[2], "OPTIONS")) menu_state = ST_OPTIONS; 
                            if (GuiButton(mm_layoutRecs[3], "QUIT")) exitWindowRequested = true; 
                            int previousAlignment = GuiGetStyle(LABEL, TEXT_ALIGNMENT);
                            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
                            GuiLabel(mm_layoutRecs[4], title);
                            GuiSetStyle(LABEL, TEXT_ALIGNMENT, previousAlignment);
                        }
                        break;
                    case ST_DIR:
                        {
                            FDGUI_Init->dir_back_button = GuiButton((Rectangle){40.0f,20.0f,100,50}, "< BACK");
                            GuiLabel((Rectangle){ (float)(SWIDTH/ 2.0f) - 100.0f, 10, 800, 50 }, directory);
                            GuiListViewEx((Rectangle){ 1, 50, (float)SWIDTH, (float)SHEIGHT - 50 },
                                files.paths, 
                                files.count, 
                                &App.FD_GUI->FDScrollIndex, 
                                &App.FD_GUI->FDItemActive,
                                &App.FD_GUI->FDItemFocused);
                        if(FDGUI_Init->dir_back_button || IsKeyPressed(KEY_BACKSPACE)){
                            TextCopy(directory, GetPrevDirectoryPath(directory));
                            // UnloadDirectoryFiles(files);
                            files = LoadDirectoryFiles(directory);
                            // listScrollIndex = 0;
                            // listItemActive = -1;
                            // listItemFocused = -1;
                        }
                        if(App.FD_GUI->FDItemActive >= 0 && (App.FD_GUI->FDItemActive < (int)files.count) && DirectoryExists(files.paths[App.FD_GUI->FDItemActive])){
                            TextCopy(directory,files.paths[App.FD_GUI->FDItemActive]);
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
                            DrawText("OPTIONS", 20, 20, 40, WHITE);

                        }
                        break;
                    case ST_LOADED:
                        {
                            DrawText("LOADED", 20, 20, 40, WHITE);

                        }
                        break;
                    default:
                        break;
                    }
                if(exitWindowRequested && menu_state != ST_SPLASH){
                    int quitboxchoice = -1;
                    const float qBoxW = 800.0f;
                    const float qBoxH = 400.0f;
                    Rectangle qBoxBounds = {
                        (SWIDTH - qBoxW)/2,
                        (SHEIGHT - qBoxH)/2,
                        qBoxW,
                        qBoxH
                    };
                    DrawRectangle(0, 0, SWIDTH, SHEIGHT, Fade(BLACK, 0.5f));
                    GuiMessageBox(qBoxBounds, GuiIconText(ICON_CIRCLE_WARNING_FILL, "Quit Application"), "Quit Birdi?", "Y;N", &quitboxchoice);
                    if(quitboxchoice == 1){
                        exitWindow = true;
                    }
                    else if (quitboxchoice == 0 || quitboxchoice == 2){
                        exitWindowRequested = false;
                    }
                }
            EndDrawing();
            }
            CloseWindow();
    }
    return EXIT_SUCCESS;
    }

static int _loadExCLI(const char* example, Settings* global_defaults, bool loader){
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



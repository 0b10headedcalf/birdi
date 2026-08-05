#include "example.h"
#include "../b_core.h"
#include <raylib.h>
#include <stdlib.h>

typedef struct{
    void* blit;
    void* walk;
}Walker;

typedef enum{
    PAUSED,
    RUNNING
}state_enum_t;

struct GameManager_t{
    state_enum_t* state_enum;
};

// static bool init = false;
//
// void inititialize(void){
//     init = true;
// }


int run(){
    // inititialize();
    Settings global_defaults = {1024,768,60,"Random Walk\0"}; 
    Settings*  Settings = &global_defaults;
    InitWindow(Settings->width, Settings->height, Settings->title);
    SetTargetFPS(Settings->currentFPS);
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
    fpsText = TextFormat("FPS: %i",GetFPS(),Settings->currentFPS);
    DrawText(fpsText,10,10,20,GREEN);
    EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}

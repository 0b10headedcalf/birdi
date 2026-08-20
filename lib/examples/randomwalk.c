#include "../birdi.h"
#include <raylib.h>
#include <stdlib.h>

typedef struct Walker{
    void* blit;
    void* walk;
}Walker;

typedef enum state_enum{
    PAUSED,
    RUNNING
}state_enum;

struct GameManager{
    state_enum* game_state;
};

// static bool init = false;
//
// void inititialize(void){
//     init = true;
// }


int load(Settings* global_defaults){
    // SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    // InitWindow(global_defaults->width, global_defaults->height, global_defaults->title);
    // SetTargetFPS(global_defaults->currentFPS);
    // while(!WindowShouldClose()){
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
    // CloseWindow();
    return EXIT_SUCCESS;
}

int run(){
    // SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    // InitWindow(global_defaults->width, global_defaults->height, global_defaults->title);
    // SetTargetFPS(global_defaults->currentFPS);
    // while(!WindowShouldClose()){
    // state_enum_t state_enum = RUNNING;
    // struct GameManager_t GameManager;
    // GameManager.state_enum = &state_enum;
    // if(IsKeyPressed(KEY_P) && GameManager.state_enum != PAUSED) {
    //     *GameManager.state_enum = PAUSED;
    // }
    // else{
    //     *GameManager.state_enum = RUNNING;
    // // }
    // // while(!init){
    // BeginDrawing();
    // ClearBackground(BLACK);   
    //
    //
    // //FPS counter
    // const char* fpsText = 0;
    // fpsText = TextFormat("FPS: %i",GetFPS(),global_defaults->currentFPS);
    // DrawText(fpsText,10,10,20,GREEN);
    // EndDrawing();
    // // CloseWindow();
    return EXIT_SUCCESS;
}

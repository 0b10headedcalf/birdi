#include "example.h"
#include <raylib.h>

int run(Settings* settings){
        BeginDrawing();
        ClearBackground(BLACK);   

        //FPS counter
        const char* fpsText = 0;
        fpsText = TextFormat("FPS: %i",GetFPS(),settings->currentFPS);
        DrawText(fpsText,10,10,20,GREEN);
        EndDrawing();
        return EXIT_SUCCESS;
}

#include "../lib/rngs/b_rand.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <threads.h>

//raylib stuff
#include "raylib.h"


struct userOptions{
    int screenWidth;
    int screenHeight;
    int targetFPS;
    char windowTitle[128];
};

int main(void) {
    while (!WindowShouldClose()) {

    }

    CloseWindow();
    return 0;
}

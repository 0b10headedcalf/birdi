#ifndef B_CORE
#define B_CORE


#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include "math/bmath.h"
#include "rngs/b_rand.h"
#include "b_string.h"
//simple math defs


//string stuff
typedef struct{
    char* data;
    size_t length;
}b_String;

b_String* conversion_fromCstring(char* in_str);
char* conversion_toCstring(b_String in_str);
b_String slice(b_String in_str, size_t startpos, size_t endpos);
b_String string_replace_at(b_String in_str, char replace, size_t index, size_t desiredIndex);
b_String fixBufOverflow(char* in_str);

//rendering


typedef struct b_color_t{
    double r;
    double g;
    double b;
    double a;
}b_Color;

//draw
void blit(Vector2 point,b_Color color);

//game stuff
//opaque type containing state (different simulations may contain a different needed state)
typedef struct GameManager GameManager;
typedef enum state_enum state_enum;

//this one should be pretty consistent
typedef struct
{
    int width;
    int height;
    float currentFPS;
    char* title;
}Settings;

#endif

#ifndef B_CORE
#define B_CORE

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


//simple math defs
double b_lerp(double a, double b, double step);

// basic RNG
uint64_t INIT_SEED(void);
double normalize64(uint64_t seed);

// PRNG algorithms
uint64_t splitmix64(uint64_t seed);
uint64_t xorshift64(uint64_t seed);


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

typedef struct{
    double x;
    double y;
}Vec2;

typedef struct{
    double x;
    double y;
    double z;
}Vec3;


//state management
typedef struct{
    float FPS;
    float time;
    uint64_t objectCount;
}state_Manager;

#endif

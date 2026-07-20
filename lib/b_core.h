#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


//simple math defs
double b_lerp(double a, double b, double step);

// basic RNG
uint64_t INIT_SEED(void);
float normalize64(uint64_t seed);
// float normalize32(uint32_t seed); #enable for edge hardware

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



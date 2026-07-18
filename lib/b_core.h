#pragma once


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct{
    char* data;
    size_t length;
}b_String_slice;

typedef struct{
    void* alloc;
    size_t offset;
}b_alloc;


double b_lerp(double a, double b, double step);


// basic RNG
uint64_t INIT_SEED(void);
float normalize64(uint64_t seed);
// float normalize32(uint32_t seed); #enable for edge hardware

// PRNG algorithms
uint64_t splitmix64(uint64_t seed);
uint64_t xorshift64(uint64_t seed);

b_String_slice* conversion_fromCstring(char* in_str);
char* conversion_toCstring(b_String_slice in_str);
b_String_slice slice(b_String_slice in_str, size_t startpos, size_t endpos);
b_String_slice string_replace_at(b_String_slice in_str, char replace, size_t index, size_t desiredIndex);
b_String_slice fixBufOverflow(char* in_str);



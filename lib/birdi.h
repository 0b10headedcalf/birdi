#ifndef BIRDI
#define BIRDI

#include <stdint.h>
#include <stddef.h>

typedef struct GameManager GameManager;
typedef enum state_enum state_enum;

typedef struct
{
    int width;
    int height;
    float currentFPS;
    const char* title;
}Settings;

typedef struct {
    const char* data;
    size_t length;
}String;

String* conversion_fromCstring(char* in_str);
char* conversion_toCstring(String in_str);
String slice(String in_str, size_t startpos, size_t endpos);
String string_replace_at(String in_str, char replace, size_t index, size_t desiredIndex);
String fixBufOverflow(char* in_str);

void INIT_SEED(uint64_t* seed); 
uint64_t splitmix64(uint64_t seed);
double normalize(int64_t n);
uint64_t xorshift64(uint64_t seed);
double b_lerp(double a, double b, double step);

#endif

#ifdef BIRDI_IMPLEMENTATION
#include <time.h>

void INIT_SEED(uint64_t* seed){
    *seed = (uint64_t)time(NULL); 
}

#endif

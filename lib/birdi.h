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
    char* title;
}Settings;

typedef struct {
    const char* data;
    size_t length;
}b_String;

b_String* conversion_fromCstring(char* in_str);
char* conversion_toCstring(b_String in_str);
b_String slice(b_String in_str, size_t startpos, size_t endpos);
b_String string_replace_at(b_String in_str, char replace, size_t index, size_t desiredIndex);
b_String fixBufOverflow(char* in_str);

void INIT_SEED(int64_t* seed); 
int64_t splitmix64(int64_t* seed);
double normalize(int64_t* seed);
int64_t xorshift64(int64_t* seed);
double b_lerp(double a, double b, double step);

#endif

#ifdef BIRDI_IMPL
#include <time.h>

void INIT_SEED(int64_t* seed){
    *seed = (uint64_t)time(NULL); 
}

#endif

#include "birdi.h"
#include <stdint.h>
#include <time.h>

void INIT_SEED(uint64_t* seed){
    *seed = (uint64_t)time(NULL); 
}

//basic prng algorithm
uint64_t splitmix64(uint64_t seed) {
    seed += 0x9e3779b97f4a7c15;
    uint64_t n = seed;
    n = (n ^ (n>>30)) * 0xbf58476d1ce4e5b9; 
    n = (n ^ (n>>27)) * 0x94d049bb133111eb;
    return n ^ (n>>31);
}

//normalizes a 64 bit integer into a value between 0&1
double normalize(uint64_t n){
    return (double)n / (double)UINT64_MAX;
}
//
// int64_t xorshift64(int64_t* seed) {
//   uint64_t state = seed;
//   state ^= state << 13;
//   state ^= state >> 7;
//   state ^= state << 17;
//   return state;
// }

// b_String* conversion_fromCstring(char* in_str){
//     size_t len = strlen(in_str);
//     b_String tmp = {NULL, len};
//     b_String* converted = malloc(sizeof(tmp));
//     for (size_t i = 0; i<len; i++) {
//         converted->data[i] = in_str[i];
//     }
//     return converted;
// }

#include "birdi.h"
#include <time.h>

void INIT_SEED(int64_t* seed){
    *seed = (uint64_t)time(NULL); 
}

// int64_t splitmix64(int64_t* seed) {
//   seed ^= seed >> 6;
//   seed *= 0x2127599bf4325c37ULL;
//   seed ^= seed << 7;
//   return seed;
// }
// double normalize64(int64_t seed) { return (float)seed / (float)UINT64_MAX; }
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

#include "../b_core.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t INIT_SEED(void) { return (uint64_t)time(NULL); }

uint64_t splitmix64(uint64_t seed) {
  seed ^= seed >> 6;
  seed *= 0x2127599bf4325c37ULL;
  seed ^= seed << 7;
  return seed;
}
//99% sure this is compiler optimized anyways
float normalize64(uint64_t seed) { return (float)seed / (float)UINT64_MAX; }

uint64_t xorshift64(uint64_t seed) {
  uint64_t state = seed;
  state ^= state << 13;
  state ^= state >> 7;
  state ^= state << 17;
  return state;
}

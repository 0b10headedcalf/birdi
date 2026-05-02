#include "birdirand.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

uint64_t INIT_SEED(void) {
  uint64_t t = (uint64_t)time(NULL);
  uint64_t *state = &t;
  // fast-hash mix function to scramble time to seed
  *state ^= *state >> 23;
  *state *= 0x2127599bf4325c37ULL;
  *state ^= *state >> 47;
  return *state;
}

long double normalize(uint64_t seed) {
  return (long double)seed / (long double)UINT64_MAX;
}

uint32_t xorshift32(uint32_t seed) {
  uint32_t state = seed;
  state ^= state << 13;
  state ^= state >> 17;
  state ^= state << 5;
  return state;
}

uint64_t xorshift64(uint64_t seed) {
  uint64_t state = seed;
  state ^= state << 13;
  state ^= state >> 7;
  state ^= state << 17;
  return state;
}

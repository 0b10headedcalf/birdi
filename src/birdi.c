#include "../lib/rngs/b_rand.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <threads.h>

int main(int argc, char *argv[]) {
  uint64_t seed = INIT_SEED();
  seed = splitmix64(seed);
  float normalized = normalize64(seed);
  printf("\nSeed: %lu", seed);
  printf("\nNormalize: %f", normalized);
  return 1;
}

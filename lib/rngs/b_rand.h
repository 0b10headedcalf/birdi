#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

// basic RNG
uint64_t INIT_SEED(void);
float normalize64(uint64_t seed);
// float normalize32(uint32_t seed); #enable for edge hardware

// PRNG algorithms
uint64_t splitmix64(uint64_t seed);
uint64_t xorshift64(uint64_t seed);

#pragma once

// sentinel for backwards compatibility
#ifndef BIRDIRAND_H_
#define BIRDIRAND_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

extern uint64_t INIT_SEED(void);
long double normalize(uint64_t seed);
uint32_t xorshift32(uint32_t seed);
uint64_t xorshift64(uint64_t seed);

#endif

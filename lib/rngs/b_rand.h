#include <stdint.h>

int64_t INIT_SEED(void); 
int64_t splitmix64(uint64_t seed);
double normalize64(uint64_t seed);
int64_t xorshift64(uint64_t seed);

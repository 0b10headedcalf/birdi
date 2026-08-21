#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "../lib/libbirdi.c"

int main(void)
{
    uint64_t seed;
    INIT_SEED(&seed);
    assert(seed == (uint64_t)time(NULL));
    return EXIT_SUCCESS;
}

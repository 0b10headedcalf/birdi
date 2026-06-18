#include <stdbool.h>
#include "bmath.h"

float b_lerp(float a, float b, float step){
    return (1-step) * a + step * b;
}





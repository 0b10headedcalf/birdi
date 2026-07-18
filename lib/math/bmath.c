#include "../b_core.h"

double b_lerp(double a, double b, double step){
    return (1-step) * a + step * b;
}





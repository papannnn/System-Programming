#include "trig_math.hpp"
#include <math.h>

double sine(double x) {
    return sin(x * (PI / 180));
}

double cosine(double x) {
    return cos(x * (PI / 180));
}
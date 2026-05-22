#include "common_math.hpp"
#include <iostream>

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    if (b == 0) {
        std::cout << "Divide by zero not allowed" << std::endl;
        return 0;
    }

    return a / b;
}

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}
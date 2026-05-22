#include "common_math/common_math.hpp"
#include "complex_math/complex_math.hpp"
#include "trig_math/trig_math.hpp"
#include <iostream>

int main () {
    double res;
    double a = 45.0, b = 90.0;
    
    res = add(a, b);
    std::cout << "Two numbers added: " << res << std::endl;
    std::cout << "Sine of a: " << sine(a) << std::endl;

    complex_n_t cres;
    complex_n_t ca, cb;
    ca.re = 1.0;
    ca.imag = 2.0;

    cb.re = 2.0;
    cb.imag = 3.0;
    cres = cadd(ca, cb);
    std::cout << "Adding two complex number: " << cres.imag << " " << cres.re << std::endl;
}
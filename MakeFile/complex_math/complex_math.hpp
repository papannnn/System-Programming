#ifndef __COMPLEX_MATH__
#define __COMPLEX_MATH__

struct complex_n_t {
    double re;
    double imag;
};

complex_n_t cadd(complex_n_t a, complex_n_t b);
complex_n_t csub(complex_n_t a, complex_n_t b);

#endif
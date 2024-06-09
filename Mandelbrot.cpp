#include "Mandelbrot.hpp"

int Mandelbrot::calculateValue(std::complex<double> complex)
{
    std::complex z{complex};
    for (int i{0}; i < iterLimit; ++i)
    {
        if (abs(z) > 4.0)
            return i;
        z = z * z + complex;
    }
    return iterLimit;
}


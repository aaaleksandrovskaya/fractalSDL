#include "Newton.hpp"

// Определение значения функции множества Ньютона
int Newton::calculateValue(std::complex<double> complex)
{
    std::complex z{complex};
    for (int i{0}; i < iterLimit; ++i)
    {
        if (abs(z) > 4.0)
            return i;
        z = z - (z * z * z * z * z + complexConst) / (5.0 * z * z * z * z);
    }
    return iterLimit;
}

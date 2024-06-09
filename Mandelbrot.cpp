#include "Mandelbrot.hpp"

int Mandelbrot::mandelbrotValue(std::complex<double> complex)
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

Fractal::Color Mandelbrot::mandelbrotColor(int x, int y)
{
    std::complex complex{x_start + x * dx, y_stop - y * dy};
    double colorIdx{(colorTableSize - 1) * mandelbrotValue(complex) / static_cast<double>(iterLimit)};
    return colorTable[static_cast<size_t>(colorIdx)];
}

#include "Fractal.hpp"

int Mandelbrot::mandelbrotValue(std::complex<double> complex)
{
    std::complex z{complex};
    for (int i{0}; i < iterLimit; ++i)
    {
        if (abs(z) > 4.0)
            return i;
        z = z*z + complex;
    }
    return iterLimit;
}

Mandelbrot::Color Mandelbrot::mandelbrotPixel(int x, int y)
{
    std::complex complex{x_start + x*dx, y_stop - y*dy};
    double val{mandelbrotValue(complex)/static_cast<double>(iterLimit)};

    if(val < 0.02)
        return Mandelbrot::Color{0, 0, 0};
    else if(val < 0.04)
        return Mandelbrot::Color{255, 0, 0};
    else if(val < 0.06)
        return Mandelbrot::Color{0, 255, 0};
    else if(val < 0.08)
        return Mandelbrot::Color{0, 0, 255};
    else if(val < 0.1)
        return Mandelbrot::Color{0, 255, 255};
    else if(val < 0.15)
        return Mandelbrot::Color{255, 0, 255};
    else if(val < 0.2)
        return Mandelbrot::Color{0, 0, 255};
    else if(val < 0.4)
        return Mandelbrot::Color{128, 255, 0};
    else if(val < 0.6)
        return Mandelbrot::Color{128, 0, 255};
    else if(val < 0.8)
        return Mandelbrot::Color{0, 255, 128};
    else if(val < 0.9)
        return Mandelbrot::Color{0, 128, 255};
    else if(val < 0.92)
        return Mandelbrot::Color{255, 0, 128};
    else if(val < 0.94)
        return Mandelbrot::Color{255, 128, 0};
    else if(val < 0.96)
        return Mandelbrot::Color{14, 59, 128};
    else if(val < 0.98)
        return Mandelbrot::Color{134, 85, 1};
    else
        return Mandelbrot::Color{255, 255, 0};
}
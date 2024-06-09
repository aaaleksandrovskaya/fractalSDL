#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP
#include <complex>
#include "Fractal.hpp"

class Mandelbrot : public Fractal
{
public:
    Mandelbrot(int width, int height)
        : Fractal(width, height), dx{(x_stop - x_start) / (width - 1)}, dy{(y_stop - y_start) / (height - 1)} {}
    Color mandelbrotColor(int x, int y);

private:
    double dx{};
    double dy{};

    int mandelbrotValue(std::complex<double> complex);
};
#endif
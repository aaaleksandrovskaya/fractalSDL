#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP
#include "Fractal.hpp"

class Mandelbrot : public Fractal
{
public:
    Mandelbrot(int width, int height, int iterLimit = 200)
        : Fractal(width, height, iterLimit, -2.0, 1.0, -1.0, 1.0) {}

private:
    int calculateValue(std::complex<double> complex);
};
#endif
#ifndef JULIA_HPP
#define JULIA_HPP
#include <complex>
#include "Fractal.hpp"

class Julia : public Fractal
{
public:
    Julia(int width, int height, int iterLimit, std::complex<double> complexConst = {-0.5, 0.6})
        : Fractal(width, height, iterLimit, -1.75, 1.75, -1.75, 1.75), complexConst{complexConst} {}

private:
    int calculateValue(std::complex<double> complex);
    std::complex<double> complexConst{};
};
#endif
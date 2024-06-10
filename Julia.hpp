#ifndef JULIA_HPP
#define JULIA_HPP
#include "Fractal.hpp"

class Julia : public Fractal
{
public:
    Julia(int width, int height, int iterLimit = 200, std::complex<double> complexConst = {-0.8, 0.156})
        : Fractal(width, height, iterLimit, -1.75, 1.75, -1.5, 1.5), complexConst{complexConst} {}

private:
    int calculateValue(std::complex<double> complex);
    std::complex<double> complexConst{};
};
#endif
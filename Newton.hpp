#ifndef NEWTON_HPP
#define NEWTON_HPP
#include "Fractal.hpp"

// Дочерний класс множества Ньютона
class Newton : public Fractal
{
public:
    Newton(int width, int height, int iterLimit = 20, std::complex<double> complexConst = {-1.0, 0.0})
        : Fractal(width, height, iterLimit, -2.0, 2.0, -2.0, 2.0), complexConst{complexConst} {}

private:
    int calculateValue(std::complex<double> complex);
    std::complex<double> complexConst{};
};
#endif
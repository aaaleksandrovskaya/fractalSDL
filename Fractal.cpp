#include "Fractal.hpp"

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

Mandelbrot::Color Mandelbrot::mandelbrotColor(int x, int y)
{
    std::complex complex{x_start + x * dx, y_stop - y * dy};
    double colorIdx{(colorTableSize - 1) * mandelbrotValue(complex) / static_cast<double>(iterLimit)};
    return colorTable[static_cast<size_t>(colorIdx)];
}

void Mandelbrot::setColorTable()
{
    std::random_device rd{};
    std::seed_seq seed{
        static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
        rd(), rd(), rd(), rd(), rd(), rd(), rd()};

    std::mt19937 mt{seed};
    std::uniform_int_distribution randomColor{0, 255};

    for (auto &elem : colorTable)
    {
        elem = {randomColor(mt), randomColor(mt), randomColor(mt)};
    }
}

std::ostream &operator<<(std::ostream &out, const Mandelbrot::Color &color)
{
    out << color.red << ' ' << color.green << ' ' << color.blue;
    return out;
}
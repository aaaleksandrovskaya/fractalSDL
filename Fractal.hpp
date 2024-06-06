#ifndef FRACTAL_HPP
#define FRACTAL_HPP
#include <complex>

class Mandelbrot
{
public:
    struct Color
    {
        int red{};
        int green{};
        int blue{};
    };
    Mandelbrot(int width, int height)
        : width{width}, height{height}, dx{(x_stop - x_start) / (width - 1)}, dy{(y_stop - y_start) / (height - 1)}
    {
    }
    Color mandelbrotPixel(int x, int y);

private:
    const int iterLimit{500};
    const double x_start{-2.0};
    const double x_stop{1.0};
    const double y_start{-1.0};
    const double y_stop{1.0};

    int width{};
    int height{};
    double dx{};
    double dy{};

    int mandelbrotValue(std::complex<double> complex);
};
#endif
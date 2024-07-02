#ifndef FRACTAL_HPP
#define FRACTAL_HPP
#include <random>
#include <chrono>
#include <iostream>
#include <complex>

// Родительский класс для фракталов
class Fractal
{
public:
    struct Color
    {
        int red{};
        int green{};
        int blue{};
    };

    Fractal(int width, int height, int iterLimit, double x_start = -1.0, double x_stop = 1.0, double y_start = -1.0, double y_stop = 1.0)
        : width{width}, height{height}, iterLimit{iterLimit}
        , x_start{x_start}, x_stop{x_stop}, y_start{y_start}, y_stop{y_stop}
        , dx{(x_stop - x_start) / (width - 1)}, dy{(y_stop - y_start) / (height - 1)}
    {
        setColorTable();
    }

    virtual ~Fractal(){}

    Color calculateColor(int x, int y);

protected:
    // Параметры фрактала
    int iterLimit{};
    double x_start{};
    double x_stop{};
    double y_start{};
    double y_stop{};
    double dx{};
    double dy{};

    // Определение значения функции фрактала, определяемое индивидуально для каждого типа фрактала
    virtual int calculateValue(std::complex<double> complex) = 0;

    // Параметры окрашивания фрактала
    constexpr static int colorTableSize{20};
    Color colorTable[colorTableSize]{};

    // Параметры окна для отрисовки фрактала
    int width{};
    int height{};

private:
    void setColorTable();

    friend std::ostream &operator<<(std::ostream &out, const Color &color);
};

#endif
#ifndef FRACTAL_HPP
#define FRACTAL_HPP
#include <random>
#include <chrono>
#include <iostream>

class Fractal
{
public:
    struct Color
    {
        int red{};
        int green{};
        int blue{};
    };

    Fractal(int width, int height)
        : width{width}, height{height}
    {
        setColorTable();
    }

protected:
    const int iterLimit{500};
    const double x_start{-2.0};
    const double x_stop{1.0};
    const double y_start{-1.0};
    const double y_stop{1.0};

    constexpr static int colorTableSize{20};
    Color colorTable[colorTableSize]{};

    int width{};
    int height{};

private:
    void setColorTable();

    friend std::ostream &operator<<(std::ostream &out, const Color &color);
};

#endif
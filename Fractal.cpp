#include "Fractal.hpp"

void Fractal::setColorTable()
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

std::ostream &operator<<(std::ostream &out, const Fractal::Color &color)
{
    out << color.red << ' ' << color.green << ' ' << color.blue;
    return out;
}
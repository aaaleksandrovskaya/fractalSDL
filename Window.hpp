#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>
#include <thread>
#include <algorithm>
#include <array>
#include <exception>
#include "Fractal.hpp"
#include "Mandelbrot.hpp"
#include "Julia.hpp"
#include "Newton.hpp"

// Класс окна SDL
class Window
{
public:
    Window(int screen_width = 640, int screen_height = 480)
        : screen_width{screen_width}, screen_height{screen_height}
    {
        createWindow();
    };
    ~Window()
    {
        destroyWindow();
    };

    void calculateWindow(Fractal &fractal, std::vector<Fractal::Color> &screen, int h_start, int height);
    void drawWindow(const std::vector<Fractal::Color> &screen, int h_start, int height);
    bool processWindow();

private:
    // Перечисление доступных типов фракталов
    enum fractalNum
    {
        MandelbrotNumber,
        JuliaNumber,
        NewtonNumber,
        LastNumber
    };

    // Параметры окна SDL
    int screen_width{};
    int screen_height{};
    SDL_Window *screen_window{};
    SDL_Renderer *gRenderer{};

    // Определение фрактала, который необходимо будет отрисовать
    fractalNum currentFractal{MandelbrotNumber};
    std::unique_ptr<Fractal> getCurrentFractal(SDL_Keycode key);

    void createWindow();
    void destroyWindow();
};
#endif

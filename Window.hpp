#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include "Fractal.hpp"

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

    int getWidth() { return screen_width; };
    int getHeight() { return screen_height; };
    void processWindow();

private:
    int screen_width{};
    int screen_height{};
    SDL_Window *screen_window{};
    SDL_Renderer *gRenderer{};

    void createWindow();
    void destroyWindow();
    bool processKey();
    void drawPixel(int x, int y, Mandelbrot mand);
};
#endif

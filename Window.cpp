#include "Window.hpp"

void threadFunc(Fractal &fractal, Window &win, std::vector<Fractal::Color> &vec, int h_start, int height)
{
    win.calculateWindow(fractal, vec, h_start, height);
}

void runDrawThreads(Fractal &fractal, Window &win, std::array<std::vector<Fractal::Color>, Window::threadNum> &vec, const int width, const int height)
{
    std::thread threads[Window::threadNum];
    int threadVecSize{static_cast<int>(std::ceil(static_cast<double>(height) / Window::threadNum))};

    for (size_t i{0}; i < (Window::threadNum - 1); ++i)
    {
        threads[i] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[i]), i * threadVecSize, threadVecSize));
    }
    threads[Window::threadNum - 1] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[Window::threadNum - 1]),
                                                           (Window::threadNum - 1) * threadVecSize, (height - (Window::threadNum - 1) * threadVecSize)));

    for (auto &thr : threads)
    {
        thr.join();
    }

    for (size_t i{0}; i < (Window::threadNum - 1); ++i)
    {
        win.drawWindow(vec[i], i * threadVecSize, threadVecSize);
    }
    win.drawWindow(vec[Window::threadNum - 1], (Window::threadNum - 1) * threadVecSize, (height - (Window::threadNum - 1) * threadVecSize));
}

void Window::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw "SDL could not initialize!";
    }
    else
    {
        screen_window = SDL_CreateWindow("Fractal",
                                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                         screen_width, screen_height, SDL_WINDOW_SHOWN);
        SDL_Surface *screenSurface{SDL_GetWindowSurface(screen_window)};
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(screen_window);
        gRenderer = SDL_CreateRenderer(screen_window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
    }
}

void Window::destroyWindow()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(screen_window);
    SDL_Quit();
}

void Window::calculateWindow(Fractal &fractal, std::vector<Fractal::Color> &screen, int h_start, int height)
{
    for (int y{h_start}; y < (h_start + height); ++y)
    {
        for (int x{0}; x < this->screen_width; ++x)
        {
            screen.push_back(fractal.calculateColor(x, y));
        }
    }
}

void Window::drawWindow(const std::vector<Fractal::Color> &screen, int h_start, int height)
{
    for (size_t idx{0}; idx < (this->screen_width * height); ++idx)
    {
        auto [r, g, b] = screen.at(idx);
        SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
        SDL_RenderDrawPoint(gRenderer, (idx % this->screen_width), h_start + (idx / this->screen_width));
    }
    SDL_RenderPresent(gRenderer);
}

bool Window::processKey()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            std::cout << "QUIT button\n";
            return true;
            break;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            std::array<std::vector<Fractal::Color>, Window::threadNum> vec{};
            Fractal *fractal{nullptr};
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "UP button\n";
                break;

            case SDLK_DOWN:
                std::cout << "DOWN button\n";
                break;

            case SDLK_LEFT:
                runDrawThreads(*getCurrentFractal(SDLK_LEFT), std::ref(*this), std::ref(vec), screen_width, screen_height);
                break;

            case SDLK_RIGHT:
                runDrawThreads(*getCurrentFractal(SDLK_RIGHT), std::ref(*this), std::ref(vec), screen_width, screen_height);
                break;

            default:
                break;
            }
        }
        return false;
    }
}

Fractal *Window::getCurrentFractal(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_LEFT:
        if (currentFractal == MandelbrotNumber)
            currentFractal = static_cast<fractalNum>(LastNumber - 1);
        else
            currentFractal = static_cast<fractalNum>(currentFractal - 1);
        break;
    case SDLK_RIGHT:
        if (currentFractal == static_cast<fractalNum>(LastNumber - 1))
            currentFractal = MandelbrotNumber;
        else
            currentFractal = static_cast<fractalNum>(currentFractal + 1);
        break;
    }

    Fractal* ptr{nullptr};
    switch (currentFractal)
    {
    case MandelbrotNumber:
        ptr = new Mandelbrot{screen_width, screen_height};
        break;
    case JuliaNumber:
        ptr = new Julia{screen_width, screen_height};
        break;
    case LastNumber:
        ptr = new Mandelbrot{screen_width, screen_height};
        break;
    }
    return ptr;
}

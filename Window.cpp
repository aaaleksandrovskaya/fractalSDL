#include "Window.hpp"

// Количество потоков для определения цветов пикселей фрактала
static constexpr int threadNum{8};

// Функция, вызываемая в каждом потоке
void threadFunc(Fractal &fractal, Window &win, std::vector<Fractal::Color> &vec, int h_start, int height)
{
    win.calculateWindow(fractal, vec, h_start, height);
}

// Создание threadNum потоков для определения цветов пикселей
// Отрисовка этих пикселей (в основном потоке)
void runDrawThreads(Fractal &fractal, Window &win, std::array<std::vector<Fractal::Color>, threadNum> &vec, const int height)
{
    // Создание threadNum потоков для определения цветов пикселей
    std::thread threads[threadNum];
    int threadVecSize{static_cast<int>(std::ceil(static_cast<double>(height) / threadNum))};

    for (size_t i{0}; i < (threadNum - 1); ++i)
    {
        threads[i] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[i]), i * threadVecSize, threadVecSize));
    }
    threads[threadNum - 1] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[threadNum - 1]),
                                                           (threadNum - 1) * threadVecSize, (height - (threadNum - 1) * threadVecSize)));

    // Ожидание завершения работы потоков
    for (auto &thr : threads)
    {
        thr.join();
    }

    // Отрисовка вычисленных значений пикселей
    for (size_t i{0}; i < (threadNum - 1); ++i)
    {
        win.drawWindow(vec[i], i * threadVecSize, threadVecSize);
    }
    win.drawWindow(vec[threadNum - 1], (threadNum - 1) * threadVecSize, (height - (threadNum - 1) * threadVecSize));
}

// Создание окна SDL и запуск потоков для отрисовки фрактала по умолчанию
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

        std::array<std::vector<Fractal::Color>, threadNum> vec{};
        runDrawThreads(*getCurrentFractal(SDLK_CAPSLOCK), std::ref(*this), std::ref(vec), screen_height);
    }
}

// Уничтожение окна SDL
void Window::destroyWindow()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(screen_window);
    SDL_Quit();
}

// Функция определения цветов пикселей для height строчек изображения, начиная с h_start
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

// Функция отрисовки height строчек изображения, начиная с h_start
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

// Функция, осуществляющая смену отображаемого фрактала по нажатию стрелок вправо/влево и выход по нажатию кнопки выход
bool Window::processWindow()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            return true;
            break;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            std::array<std::vector<Fractal::Color>, threadNum> vec{};
            Fractal *fractal{nullptr};
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                runDrawThreads(*getCurrentFractal(SDLK_LEFT), std::ref(*this), std::ref(vec), screen_height);
                break;

            case SDLK_RIGHT:
                runDrawThreads(*getCurrentFractal(SDLK_RIGHT), std::ref(*this), std::ref(vec), screen_height);
                break;

            default:
                break;
            }
        }
        return false;
    }
}

// Функция, возвращающая указатель на фрактал, который нужно будет отрисовать после нажатия на клавишу key
std::unique_ptr<Fractal> Window::getCurrentFractal(SDL_Keycode key)
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

    std::unique_ptr<Fractal> ptr{nullptr};
    switch (currentFractal)
    {
    case MandelbrotNumber:
        ptr = std::make_unique<Mandelbrot>(screen_width, screen_height);
        break;
    case JuliaNumber:
        ptr = std::make_unique<Julia>(screen_width, screen_height);
        break;
    case NewtonNumber:
        ptr = std::make_unique<Newton>(screen_width, screen_height);
        break;
    default:
        ptr = std::make_unique<Mandelbrot>(screen_width, screen_height);
        break;
    }
    return ptr;
}

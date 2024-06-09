#include <iostream>
#include <thread>
#include <algorithm>
#include "Window.hpp"

constexpr int threadNum{8};
void threadFunc(Fractal &fractal, Window &win, std::vector<Fractal::Color> &vec, int h_start, int height)
{
    win.calculateWindow(fractal, vec, h_start, height);
}

void runDrawThreads(Fractal &fractal, Window &win, std::array<std::vector<Fractal::Color>, threadNum> &vec, const int width, const int height)
{
    std::thread threads[threadNum];
    int threadVecSize{static_cast<int>(std::ceil(static_cast<double>(height) / threadNum))};

    for (size_t i{0}; i < (threadNum - 1); ++i)
    {
        threads[i] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[i]), i * threadVecSize, threadVecSize));
    }
    threads[threadNum - 1] = std::move(std::thread(threadFunc, std::ref(fractal), std::ref(win), std::ref(vec[threadNum - 1]),
                                                   (threadNum - 1) * threadVecSize, (height - (threadNum - 1) * threadVecSize)));

    for (auto &thr : threads)
    {
        thr.join();
    }    
    
    for (size_t i{0}; i < (threadNum - 1); ++i)
    {
        win.drawWindow(vec[i], i * threadVecSize, threadVecSize);
    }
    win.drawWindow(vec[threadNum - 1], (threadNum - 1) * threadVecSize, (height - (threadNum - 1) * threadVecSize));
}

int main()
{
    try
    {
        Window win{};
        const int winWidth{win.getWidth()};
        const int winHeight{win.getHeight()};
        Mandelbrot mand{winWidth, winHeight, 500};
        Julia jul{winWidth, winHeight, 500};

        std::array<std::vector<Fractal::Color>, threadNum> vec{};
        runDrawThreads(std::ref(jul), std::ref(win), std::ref(vec), winWidth, winHeight);

        bool quit{false};
        while (!quit)
        {
            quit |= win.processKey();
        }
    }
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << '\n';
    }

    return 0;
}
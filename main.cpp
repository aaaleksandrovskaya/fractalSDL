#include <iostream>
#include <thread>
#include <algorithm>
#include "Window.hpp"

void threadFunc(Mandelbrot &mand, Window &win, std::vector<Fractal::Color> &vec, int h_start, int height)
{
    win.calculateWindow(mand, vec, h_start, height);
}

int main()
{
    try
    {
        Window win{};
        const int winWidth{win.getWidth()};
        const int winHeight{win.getHeight()};
        Mandelbrot mand{winWidth, winHeight};

        constexpr int threadNum{8};
        std::thread threads[threadNum];
        std::vector<Fractal::Color> vec[threadNum]{};
        int threadVecSize{static_cast<int>(std::ceil(static_cast<double>(winHeight) / threadNum))};
        for (size_t i{0}; i < (threadNum - 1); ++i)
        {
            threads[i] = std::move(std::thread(threadFunc, std::ref(mand), std::ref(win), std::ref(vec[i]), i * threadVecSize, threadVecSize));
        }
        threads[threadNum - 1] = std::move(std::thread(threadFunc, std::ref(mand), std::ref(win), std::ref(vec[threadNum - 1]),
                                                       (threadNum - 1) * threadVecSize, (winHeight - (threadNum - 1) * threadVecSize)));

        for (auto &thr : threads)
        {
            thr.join();
        }

        for (size_t i{0}; i < (threadNum - 1); ++i)
        {
            win.drawWindow(vec[i], i * threadVecSize, threadVecSize);
        }
        win.drawWindow(vec[threadNum - 1], (threadNum - 1) * threadVecSize, (winHeight - (threadNum - 1) * threadVecSize));

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
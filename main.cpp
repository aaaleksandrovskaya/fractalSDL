#include <iostream>
#include <thread>
#include "Window.hpp"

int main()
{
    try
    {
        Window win{};
        const int winWidth{win.getWidth()};
        const int winHeight{win.getHeight()};

        win.drawWindow(0, 0, winWidth-1, winHeight - 1);
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
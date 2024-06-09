#include <iostream>
#include "Window.hpp"

int main()
{
    try
    {
        Window win{};
        const int winWidth{win.getWidth()};
        const int winHeight{win.getHeight()};

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
#include <iostream>
#include "Window.hpp"

int main()
{
    try
    {
        Window win{};
        bool quit{false};
        while (!quit)
        {
            quit |= win.processWindow();
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << '\n';
    }

    return 0;
}
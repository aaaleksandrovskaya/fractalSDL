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
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << '\n';
    }

    return 0;
}
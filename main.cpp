#include <iostream>
#include "Window.hpp"

int main()
{
    try
    {
        Window win{};
        win.processWindow();
    }
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << '\n';
    }

    return 0;
}
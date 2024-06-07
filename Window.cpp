#include "Window.hpp"

void Window::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw "SDL could not initialize!";
    }
    else
    {
        screen_window = SDL_CreateWindow("SDL Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  screen_width, screen_height, SDL_WINDOW_SHOWN);
        SDL_Surface *screenSurface{SDL_GetWindowSurface(screen_window)};
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(screen_window);
        gRenderer = SDL_CreateRenderer(screen_window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
        SDL_RenderClear( gRenderer );
    }
}

void Window::destroyWindow()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(screen_window);
    SDL_Quit();
}

void Window::drawWindow(int w_left_top, int h_left_top, int width, int height) {
    Mandelbrot mand{screen_width, screen_height};
    for(int x{0}; x<screen_width; ++x){
        for(int y{0}; y<screen_height; ++y){
            drawPixel(x, y, mand);
        }
    }
    SDL_RenderPresent(gRenderer);
};

void Window::drawPixel(int x, int y, Mandelbrot mand)
{
    auto [r, g, b] = mand.mandelbrotColor(x, y);
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
    SDL_RenderDrawPoint(gRenderer, x, y);
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
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "UP button\n";
                break;

            case SDLK_DOWN:
                std::cout << "DOWN button\n";
                break;

            case SDLK_LEFT:
                std::cout << "LEFT button\n";
                break;

            case SDLK_RIGHT:
                std::cout << "RIGHT button\n";
                break;

            default:
                std::cout << "Another button\n";
                break;
            }
        }
        return false;
    }
}

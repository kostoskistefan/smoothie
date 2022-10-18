#include "smoothie_window.h"
#include "../utilitites.h"

SmoothieWindow::SmoothieWindow()
{
    this->stillRunning = true;
    this->window = NULL;
    this->surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        Utilities::exit_failure("Failed to initialize SDL!\n");

    this->window = SDL_CreateWindow("Smoothie",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WindowFlags::SDL_WINDOW_SHOWN);

    if (this->window == NULL)
        Utilities::exit_failure("Failed to create window!\n");

    this->surface = SDL_GetWindowSurface(this->window);

    if (this->surface == NULL)
        Utilities::exit_failure("Failed to get window surface!\n");

    SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 255, 255, 255));
}

SmoothieWindow::~SmoothieWindow()
{
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SmoothieWindow::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                this->stillRunning = false;
                break;
        }
    }

    SDL_UpdateWindowSurface(this->window);
}

bool SmoothieWindow::isRunning()
{
    return this->stillRunning;   
}
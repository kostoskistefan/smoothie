#ifndef SMOOTHIE_WINDOW_H
#define SMOOTHIE_WINDOW_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class SmoothieWindow
{
public:
    SmoothieWindow();
    ~SmoothieWindow();
    
    void update();
    bool isRunning();

private:
    bool stillRunning;

    SDL_Window *window;
    SDL_Surface *surface;
};

#endif // SMOOTHIE_WINDOW_H
#ifndef SMOOTHIE_H
#define SMOOTHIE_H

#include "joystick.h"
#include "keyboard.h"
#include "ui/smoothie_window.h"

class Smoothie
{
public:
    Smoothie();
    ~Smoothie();
    void run();

private:
    Joystick joystick;
    Keyboard keyboard;
    SmoothieWindow *window;
};

#endif // SMOOTHIE_H
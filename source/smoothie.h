#ifndef SMOOTHIE_H
#define SMOOTHIE_H

#include "joystick.h"
#include "keyboard.h"

class Smoothie
{
public:
    Smoothie();
    void run();

private:
    Joystick joystick;
    Keyboard keyboard;
};

#endif // SMOOTHIE_H
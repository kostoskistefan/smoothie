#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <linux/uinput.h>
#include <sigc++/sigc++.h>

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();
    void handle_keys();
    sigc::signal<void(int)> steer;
    sigc::signal<void(int, int)> brake;
    sigc::signal<void(int, int)> accelerate;
    sigc::signal<void(float)> actionKey;

private:
    int fileDescriptor;
    struct input_event event;
};

#endif // KEYBOARD_H
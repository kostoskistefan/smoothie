#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include <array>
#include <string>
#include <sigc++/sigc++.h>
#include "settings.h"

#if defined(__linux__) || defined(__unix__)
    #include <linux/uinput.h>
#endif

#define KEY_PRESSED  1
#define KEY_RELEASED 0

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();
    void handle_keys();
    sigc::signal<void(int)> signal_steer();
    sigc::signal<void(int, int)> signal_brake();
    sigc::signal<void(int, int)> signal_accelerate();
    sigc::signal<void(float)> signal_actionKey();

protected:
    sigc::signal<void(int)> steer;
    sigc::signal<void(int, int)> brake;
    sigc::signal<void(int, int)> accelerate;
    sigc::signal<void(float)> actionKey;

private:
    int fileDescriptor;
    struct input_event event;
    Settings settings;
};

#endif // KEYBOARD_H
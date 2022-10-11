#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "prototypes.h"
#include <linux/uinput.h>

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();
    void handle_keys(game_config_t *gameConfig);

private:
    int fileDescriptor;
    struct input_event event;
};

#endif // KEYBOARD_H
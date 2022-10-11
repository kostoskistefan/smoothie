#include "keyboard.h"
#include "utilitites.h"
#include <fcntl.h>
#include <unistd.h>

Keyboard::Keyboard()
{
    fileDescriptor = open("/dev/input/event4", O_RDONLY);

    if (fileDescriptor < 0)
        Utilities::exit_failure("Failed to open keyboard at /dev/input/event4");
}

Keyboard::~Keyboard()
{
    ioctl(fileDescriptor, UI_DEV_DESTROY);
    close(fileDescriptor);
}

void Keyboard::handle_keys()
{
    if (read(fileDescriptor, &event, sizeof(struct input_event)) < 0)
        Utilities::exit_failure("Failed to open keyboard file descriptor");

    if (event.type != EV_KEY)
        return;

    if (event.value)
    {
        switch (event.code)
        {
        case KEY_Z:
            actionKey.emit(0.6);
            break;
        case KEY_X:
            actionKey.emit(0.7);
            break;
        case KEY_C:
            actionKey.emit(0.8);
            break;
        case KEY_V:
            actionKey.emit(0.9);
            break;
        case KEY_B:
            actionKey.emit(1.0);
            break;
        case KEY_UP:
            accelerate.emit(BTN_Y, 1);
            break;
        case KEY_DOWN:
            brake.emit(BTN_X, 1);
            break;
        case KEY_LEFT:
            steer.emit(-1);
            break;
        case KEY_RIGHT:
            steer.emit(1);
            break;
        }
    }

    else 
    {
        if (event.code == KEY_UP)
            accelerate.emit(BTN_Y, 0);
        
        else if (event.code == KEY_DOWN)
            brake.emit(BTN_X, 0);

        else if (event.code == KEY_LEFT || event.code == KEY_RIGHT)
            steer.emit(0);
    }
}
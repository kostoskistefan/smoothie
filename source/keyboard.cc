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

void Keyboard::handle_keys(game_config_t *gameConfig)
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
            gameConfig->steerPercentage = 0.6f;
            break;
        case KEY_X:
            gameConfig->steerPercentage = 0.7f;
            break;
        case KEY_C:
            gameConfig->steerPercentage = 0.8f;
            break;
        case KEY_V:
            gameConfig->steerPercentage = 0.9f;
            break;
        case KEY_B:
            gameConfig->steerPercentage = 1.0f;
            break;
        case KEY_UP:
            gameConfig->accelerate = 1;
            break;
        case KEY_DOWN:
            gameConfig->brake = 1;
            break;
        case KEY_LEFT:
            gameConfig->steerDirection = -1;
            break;
        case KEY_RIGHT:
            gameConfig->steerDirection = 1;
            break;
        }
    }

    else 
    {
        if (event.code == KEY_UP)
            gameConfig->accelerate = 0;
        
        else if (event.code == KEY_DOWN)
            gameConfig->brake = 0;

        else if (event.code == KEY_LEFT || event.code == KEY_RIGHT)
            gameConfig->steerDirection = 0;
    }
}
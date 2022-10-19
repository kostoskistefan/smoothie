#include "keyboard.h"
#include "utilitites.h"
#include "key_map.h"
#include <fcntl.h>
#include <unistd.h>

Keyboard::Keyboard()
{
    this->fileDescriptor = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);

    if (this->fileDescriptor < 0)
        Utilities::exit_failure("Failed to open keyboard at /dev/input/event4");
}

Keyboard::~Keyboard()
{
    ioctl(this->fileDescriptor, UI_DEV_DESTROY);
    close(this->fileDescriptor);
}

void Keyboard::handle_keys()
{
    bool eventHasHappened = read(this->fileDescriptor, &this->event, sizeof(struct input_event)) >= 0;

    if (!eventHasHappened)
        return;

    bool eventIsAKeyEvent = this->event.type == EV_KEY;

    if (!eventIsAKeyEvent)
        return;

    switch (this->event.value)
    {
    case KEY_PRESSED:
        // Action keys
        for (int i = 1; i <= 10; i++)
            if (this->event.code == settings.get_keys().actionKeys[i - 1])
                this->actionKey.emit(0.1 * i);

        // Accelerate key
        if (this->event.code == settings.get_keys().accelerate)
            this->accelerate.emit(BTN_Y, 1);

        // Brake key
        else if (this->event.code == settings.get_keys().brake)
            this->brake.emit(BTN_X, 1);

        // Steer left key
        else if (this->event.code == settings.get_keys().steerLeft)
            this->steer.emit(-1);

        // Steer right key
        else if (this->event.code == settings.get_keys().steerRight)
            this->steer.emit(1);

        break;

    case KEY_RELEASED:
        // Accelerate key
        if (this->event.code == settings.get_keys().accelerate)
            this->accelerate.emit(BTN_Y, 0);

        // Brake key
        else if (this->event.code == settings.get_keys().brake)
            this->brake.emit(BTN_X, 0);

        // Steering keys
        else if (this->event.code == settings.get_keys().steerLeft ||
                 this->event.code == settings.get_keys().steerRight)
            this->steer.emit(0);

        break;
    }
}

sigc::signal<void(int)> Keyboard::signal_steer()
{
    return this->steer;
}

sigc::signal<void(int, int)> Keyboard::signal_brake()
{
    return this->brake;
}

sigc::signal<void(int, int)> Keyboard::signal_accelerate()
{
    return this->accelerate;
}

sigc::signal<void(float)> Keyboard::signal_actionKey()
{
    return this->actionKey;
}

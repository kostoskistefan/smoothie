#include "keyboard.h"
#include "utilitites.h"
#include <fcntl.h>
#include <unistd.h>

Keyboard::Keyboard()
{
    this->fileDescriptor = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);

    if (this->fileDescriptor < 0)
        Utilities::exit_failure("Failed to open keyboard at /dev/input/event4");
    
    initialize_key_definitions();

    for (size_t i = 0; i < 10; i++)
    {
        // printf("Select key %ld:\t", i);
        // std::cin >> this->keys.at(i);

        this->keys.at(i) = std::to_string((i + 1) % 10);
    }

    this->keys.at(10) = "I";
    this->keys.at(11) = "K";
    this->keys.at(12) = "J";
    this->keys.at(13) = "L";

}

Keyboard::~Keyboard()
{
    ioctl(this->fileDescriptor, UI_DEV_DESTROY);
    close(this->fileDescriptor);
}

void Keyboard::initialize_key_definitions()
{
    this->keyDefinitions = {
        { "A", KEY_A },
        { "B", KEY_B },
        { "C", KEY_C },
        { "D", KEY_D },
        { "E", KEY_E },
        { "F", KEY_F },
        { "G", KEY_G },
        { "H", KEY_H },
        { "I", KEY_I },
        { "J", KEY_J },
        { "K", KEY_K },
        { "L", KEY_L },
        { "M", KEY_M },
        { "N", KEY_N },
        { "O", KEY_O },
        { "P", KEY_P },
        { "Q", KEY_Q },
        { "R", KEY_R },
        { "S", KEY_S },
        { "T", KEY_T },
        { "U", KEY_U },
        { "V", KEY_V },
        { "W", KEY_W },
        { "X", KEY_X },
        { "Y", KEY_Y },
        { "Z", KEY_Z },

        { "0", KEY_0 },
        { "1", KEY_1 },
        { "2", KEY_2 },
        { "3", KEY_3 },
        { "4", KEY_4 },
        { "5", KEY_5 },
        { "6", KEY_6 },
        { "7", KEY_7 },
        { "8", KEY_8 },
        { "9", KEY_9 },

        { "KP0", KEY_KP0 },
        { "KP1", KEY_KP1 },
        { "KP2", KEY_KP2 },
        { "KP3", KEY_KP3 },
        { "KP4", KEY_KP4 },
        { "KP5", KEY_KP5 },
        { "KP6", KEY_KP6 },
        { "KP7", KEY_KP7 },
        { "KP8", KEY_KP8 },
        { "KP9", KEY_KP9 },

        { "KPDOT", KEY_KPDOT },
        { "KPPLUS", KEY_KPPLUS },
        { "KPSLASH", KEY_KPSLASH },
        { "KPMINUS", KEY_KPMINUS },
        { "KPENTER", KEY_KPENTER },
        { "KPASTERISK", KEY_KPASTERISK },

        { "DOT", KEY_DOT },
        { "COMMA", KEY_COMMA },
        { "SLASH", KEY_SLASH },
        { "MINUS", KEY_MINUS },
        { "EQUAL", KEY_EQUAL },
        { "LEFTBRACE", KEY_LEFTBRACE },
        { "BACKSLASH", KEY_BACKSLASH },
        { "SEMICOLON", KEY_SEMICOLON },
        { "RIGHTBRACE", KEY_RIGHTBRACE },
        { "APOSTROPHE", KEY_APOSTROPHE },

        { "TAB", KEY_TAB },
        { "SPACE", KEY_SPACE },
        { "ENTER", KEY_ENTER },
        { "BACKSPACE", KEY_BACKSPACE },

        { "UP", KEY_UP },
        { "DOWN", KEY_DOWN },
        { "LEFT", KEY_LEFT },
        { "RIGHT", KEY_RIGHT },

        { "F1", KEY_F1 },
        { "F2", KEY_F2 },
        { "F3", KEY_F3 },
        { "F4", KEY_F4 },
        { "F5", KEY_F5 },
        { "F6", KEY_F6 },
        { "F7", KEY_F7 },
        { "F8", KEY_F8 },
        { "F9", KEY_F9 },
        { "F10", KEY_F10 },
        { "F11", KEY_F11 },
        { "F12", KEY_F12 },

        { "END", KEY_END },
        { "ESC", KEY_ESC },
        { "HOME", KEY_HOME },
        { "PRINT", KEY_PRINT },
        { "INSERT", KEY_INSERT },
        { "DELETE", KEY_DELETE },
        { "PAGEUP", KEY_PAGEUP },
        { "PAGEDOWN", KEY_PAGEDOWN },
    };
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
                if (this->event.code == this->keyDefinitions.at(this->keys.at(i - 1)))
                    this->actionKey.emit(0.1 * i);

            // Accelerate key
            if (this->event.code == this->keyDefinitions.at(this->keys.at(10)))
                this->accelerate.emit(BTN_Y, 1);

            // Brake key
            else if (this->event.code == this->keyDefinitions.at(this->keys.at(11)))
                this->brake.emit(BTN_X, 1);

            // Steer left key
            else if (this->event.code == this->keyDefinitions.at(this->keys.at(12)))
                this->steer.emit(-1);

            // Steer right key
            else if (this->event.code == this->keyDefinitions.at(this->keys.at(13)))
                this->steer.emit(1);

            break;

        case KEY_RELEASED:
            // Accelerate key
            if (this->event.code == this->keyDefinitions.at(this->keys.at(10)))
                this->accelerate.emit(BTN_Y, 0);
            
            // Brake key
            else if (this->event.code == this->keyDefinitions.at(this->keys.at(11)))
                this->brake.emit(BTN_X, 0);

            // Steering keys
            else if (this->event.code == this->keyDefinitions.at(this->keys.at(12)) ||
                this->event.code == this->keyDefinitions.at(this->keys.at(13)))
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

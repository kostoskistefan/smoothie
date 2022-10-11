#include <string>
#include <csignal>
#include "joystick.h"
#include "keyboard.h"
#include "prototypes.h"
#include <linux/input-event-codes.h>

#define unused(x) ((void) x)

bool keep_running = true;

void quit(int)
{
    keep_running = false;
}

int main(int argc, char const **argv)
{
    unused(argc);
    unused(argv);

    signal(SIGINT, quit);

    Joystick joystick;
    Keyboard keyboard;

    game_config_t gameConfig = {
        .brake = 0,
        .accelerate = 0,
        .steerDirection = 0,
        .steerPercentage = 1.0f
    };

    while (keep_running)
    {
        keyboard.handle_keys(&gameConfig);

        joystick.emit_button_event(BTN_X, gameConfig.brake);
        joystick.emit_button_event(BTN_Y, gameConfig.accelerate);
        joystick.emit_axis_event(ABS_X, gameConfig.steerDirection * gameConfig.steerPercentage * INT16_MAX);
    }

    return 0;
}

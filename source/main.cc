#include <csignal>
#include "joystick.h"
#include "keyboard.h"
#include <sigc++/sigc++.h>
#include <linux/input-event-codes.h>

#define unused(x) ((void)x)

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

    keyboard.brake.connect(sigc::mem_fun(joystick, &Joystick::emit_button_event));
    keyboard.accelerate.connect(sigc::mem_fun(joystick, &Joystick::emit_button_event));

    keyboard.steer.connect(sigc::mem_fun(joystick, &Joystick::set_direction));
    keyboard.actionKey.connect(sigc::mem_fun(joystick, &Joystick::set_percentage));

    while (keep_running)
    {
        keyboard.handle_keys();
        joystick.emit_x_axis_event();
    }

    return 0;
}

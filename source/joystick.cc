#include "joystick.h"
#include "utilitites.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>

Joystick::Joystick()
{
    fileDescriptor = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (fileDescriptor < 0)
        Utilities::exit_failure("Failed to add joystick at /dev/uinput");

    initialize_controller();

    if (ioctl(fileDescriptor, UI_DEV_CREATE) < 0)
        Utilities::exit_failure("Failed to create virtual device");

    direction = 0;
    percentage = 1.0;
}

Joystick::~Joystick()
{
    ioctl(fileDescriptor, UI_DEV_DESTROY);
    close(fileDescriptor);
}

void Joystick::initialize_axes()
{
    if (ioctl(fileDescriptor, UI_SET_EVBIT, EV_ABS) < 0)
        Utilities::exit_failure("Failed to set EV_ABS");

    ioctl(fileDescriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(fileDescriptor, UI_SET_ABSBIT, ABS_Y);
}

void Joystick::initialize_buttons()
{
    if (ioctl(fileDescriptor, UI_SET_EVBIT, EV_KEY) < 0)
        Utilities::exit_failure("Failed to set EV_KEY");

    // We have to add the 4 buttons (A, B, X, Y), because 
    // Steam doesn't recognize the controller without them
    ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_A);
    ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_B);
    ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_X);
    ioctl(fileDescriptor, UI_SET_KEYBIT, BTN_Y);
}

void Joystick::initialize_controller()
{
    initialize_axes();
    initialize_buttons();    

    struct uinput_user_dev user_dev = {
        .name = "Smoothie Controller",
        .id = {
            .bustype = BUS_VIRTUAL,
            .vendor = 0x044F,
            .product = 0x0F07,
            .version = 1
        }
    };

    write(fileDescriptor, &user_dev, sizeof(struct uinput_user_dev));
}

void Joystick::emit_generic_event(short unsigned type, short unsigned code, int value)
{
    struct input_event event = {
        .time = {
            .tv_sec = 0,
            .tv_usec = 0
        },
        .type = type,
        .code = code,
        .value = value
    };

    write(fileDescriptor, &event, sizeof(event));
}

void Joystick::emit_x_axis_event()
{
    emit_generic_event(EV_ABS, ABS_X, direction * percentage * INT16_MAX);
    emit_generic_event(EV_SYN, SYN_REPORT, 0);
}

void Joystick::emit_button_event(short unsigned button, int value)
{
    emit_generic_event(EV_KEY, button, value);
    emit_generic_event(EV_SYN, SYN_REPORT, 0);
}

void Joystick::set_percentage(float percentage)
{
    this->percentage = percentage;
}

void Joystick::set_direction(int direction)
{
    this->direction = direction;
}
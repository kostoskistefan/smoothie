#include "joystick.h"
#include "utilitites.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>

Joystick::Joystick()
{
    this->fileDescriptor = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (this->fileDescriptor < 0)
        Utilities::exit_failure("Failed to add joystick at /dev/uinput");

    initialize_controller();

    if (ioctl(this->fileDescriptor, UI_DEV_CREATE) < 0)
        Utilities::exit_failure("Failed to create virtual device");

    this->direction = 0;
    this->percentage = 1.0;
}

Joystick::~Joystick()
{
    ioctl(this->fileDescriptor, UI_DEV_DESTROY);
    close(this->fileDescriptor);
}

void Joystick::initialize_axes()
{
    if (ioctl(this->fileDescriptor, UI_SET_EVBIT, EV_ABS) < 0)
        Utilities::exit_failure("Failed to set EV_ABS");

    ioctl(this->fileDescriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(this->fileDescriptor, UI_SET_ABSBIT, ABS_Y);
}

void Joystick::initialize_buttons()
{
    if (ioctl(this->fileDescriptor, UI_SET_EVBIT, EV_KEY) < 0)
        Utilities::exit_failure("Failed to set EV_KEY");

    // We have to add the 4 buttons (A, B, X, Y), because 
    // Steam doesn't recognize the controller without them
    ioctl(this->fileDescriptor, UI_SET_KEYBIT, BTN_A);
    ioctl(this->fileDescriptor, UI_SET_KEYBIT, BTN_B);
    ioctl(this->fileDescriptor, UI_SET_KEYBIT, BTN_X);
    ioctl(this->fileDescriptor, UI_SET_KEYBIT, BTN_Y);
}

void Joystick::initialize_controller()
{
    initialize_axes();
    initialize_buttons();    

    struct uinput_user_dev userDev = {
        .name = "Smoothie Virtual Controller",
        .id = {
            .bustype = BUS_VIRTUAL,
            .vendor = 0x044F,
            .product = 0x0F07,
            .version = 1
        }
    };

    write(this->fileDescriptor, &userDev, sizeof(struct uinput_user_dev));
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

    write(this->fileDescriptor, &event, sizeof(struct input_event));
}

void Joystick::emit_x_axis_event()
{
    emit_generic_event(EV_ABS, ABS_X, this->direction * this->percentage * INT16_MAX);
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

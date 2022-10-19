#include "smoothie.h"

Smoothie::Smoothie()
{
    this->keyboard.signal_brake().connect(
        sigc::mem_fun(this->joystick, &Joystick::emit_button_event));

    this->keyboard.signal_accelerate().connect(
        sigc::mem_fun(this->joystick, &Joystick::emit_button_event));

    this->keyboard.signal_steer().connect(
        sigc::mem_fun(this->joystick, &Joystick::set_direction));

    this->keyboard.signal_actionKey().connect(
        sigc::mem_fun(this->joystick, &Joystick::set_percentage));
}

void Smoothie::run()
{
    while (true)
    {
        this->keyboard.handle_keys();
        this->joystick.emit_x_axis_event();
    }
}
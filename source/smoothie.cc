#include "smoothie.h"

Smoothie::Smoothie()
{
    this->window = new SmoothieWindow();

    this->keyboard.signal_brake().connect(
        sigc::mem_fun(this->joystick, &Joystick::emit_button_event));

    this->keyboard.signal_accelerate().connect(
        sigc::mem_fun(this->joystick, &Joystick::emit_button_event));

    this->keyboard.signal_steer().connect(
        sigc::mem_fun(this->joystick, &Joystick::set_direction));

    this->keyboard.signal_actionKey().connect(
        sigc::mem_fun(this->joystick, &Joystick::set_percentage));
}

Smoothie::~Smoothie()
{
    delete this->window;
}

void Smoothie::run()
{
    do
    {
        this->window->update();
        this->keyboard.handle_keys();
        this->joystick.emit_x_axis_event();
    } while (this->window->isRunning());
}
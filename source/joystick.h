#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick
{
public:
    Joystick();
    ~Joystick();
    void emit_axis_event(short unsigned axis, int value);
    void emit_button_event(short unsigned button, int value);

private:
    int fileDescriptor;
    void initialize_axes();
    void initialize_buttons();
    void initialize_controller();
    void emit_generic_event(short unsigned type, short unsigned code, int value);
};

#endif // JOYSTICK_H
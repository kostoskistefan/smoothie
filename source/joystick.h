#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick
{
public:
    Joystick();
    ~Joystick();

    void set_direction(int direction);
    void set_percentage(float percentage);

    void emit_x_axis_event();
    void emit_button_event(short unsigned button, int value);

private:
    int direction;
    float percentage;
    int fileDescriptor;

    void initialize_axes();
    void initialize_buttons();
    void initialize_controller();
    void emit_generic_event(short unsigned type, short unsigned code, int value);
};

#endif // JOYSTICK_H
#ifndef SMOOTHIE_KEYS_H
#define SMOOTHIE_KEYS_H

#include <array>

class SmoothieKeys
{
public:
    SmoothieKeys();

    int brake;
    int accelerate;

    int steerLeft;
    int steerRight;

    std::array<int, 10> actionKeys;
};

#endif // SMOOTHIE_KEYS_H
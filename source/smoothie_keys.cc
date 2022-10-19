#include "smoothie_keys.h"

#if defined(__linux__) || defined(__unix__)
    #include <linux/input-event-codes.h>
#endif

SmoothieKeys::SmoothieKeys()
{
    this->accelerate = KEY_RESERVED;
    this->brake = KEY_RESERVED;
    this->steerLeft = KEY_RESERVED;
    this->steerRight = KEY_RESERVED;

    for (int i = 0; i < 10; i++)
        this->actionKeys[i] = KEY_RESERVED;
}
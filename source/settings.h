#ifndef SETTINGS_H
#define SETTINGS_H

#include <array>
#include <string>
#include "key_map.h"
#include "smoothie_keys.h"
#include "settings_parser.h"

class Settings
{
public:
    Settings();
    void load();
    SmoothieKeys get_keys();

private:
    SmoothieKeys keys;
    SettingsParser parser;
};

#endif // SETTINGS_H
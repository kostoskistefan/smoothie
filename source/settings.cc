#include "settings.h"
#include "utilitites.h"

Settings::Settings()
{
    if (!parser.settings_file_exists())
        parser.load_defaults();
        
    load();
}

void Settings::load()
{
    auto settings = parser.read();

    keys.accelerate = KeyMap::get_key_code_from_name(settings["Accelerate"]);
    keys.brake = KeyMap::get_key_code_from_name(settings["Brake"]);
    keys.steerLeft = KeyMap::get_key_code_from_name(settings["Steer Left"]);
    keys.steerRight = KeyMap::get_key_code_from_name(settings["Steer Right"]);

    for (int i = 0; i < 10; i++)
        keys.actionKeys[i] = KeyMap::get_key_code_from_name(settings["Action Key " + std::to_string(i + 1)]);
}


SmoothieKeys Settings::get_keys()
{
    return keys;
}
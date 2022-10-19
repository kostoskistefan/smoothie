#include "key_map.h"
#include <linux/input-event-codes.h>

std::map<std::string, int> KeyMap::keyDefinitions = {
    {"A", KEY_A},
    {"B", KEY_B},
    {"C", KEY_C},
    {"D", KEY_D},
    {"E", KEY_E},
    {"F", KEY_F},
    {"G", KEY_G},
    {"H", KEY_H},
    {"I", KEY_I},
    {"J", KEY_J},
    {"K", KEY_K},
    {"L", KEY_L},
    {"M", KEY_M},
    {"N", KEY_N},
    {"O", KEY_O},
    {"P", KEY_P},
    {"Q", KEY_Q},
    {"R", KEY_R},
    {"S", KEY_S},
    {"T", KEY_T},
    {"U", KEY_U},
    {"V", KEY_V},
    {"W", KEY_W},
    {"X", KEY_X},
    {"Y", KEY_Y},
    {"Z", KEY_Z},

    {"0", KEY_0},
    {"1", KEY_1},
    {"2", KEY_2},
    {"3", KEY_3},
    {"4", KEY_4},
    {"5", KEY_5},
    {"6", KEY_6},
    {"7", KEY_7},
    {"8", KEY_8},
    {"9", KEY_9},

    {"KP0", KEY_KP0},
    {"KP1", KEY_KP1},
    {"KP2", KEY_KP2},
    {"KP3", KEY_KP3},
    {"KP4", KEY_KP4},
    {"KP5", KEY_KP5},
    {"KP6", KEY_KP6},
    {"KP7", KEY_KP7},
    {"KP8", KEY_KP8},
    {"KP9", KEY_KP9},

    {"KPDOT", KEY_KPDOT},
    {"KPPLUS", KEY_KPPLUS},
    {"KPSLASH", KEY_KPSLASH},
    {"KPMINUS", KEY_KPMINUS},
    {"KPENTER", KEY_KPENTER},
    {"KPASTERISK", KEY_KPASTERISK},

    {"DOT", KEY_DOT},
    {"COMMA", KEY_COMMA},
    {"SLASH", KEY_SLASH},
    {"MINUS", KEY_MINUS},
    {"EQUAL", KEY_EQUAL},
    {"LEFTBRACE", KEY_LEFTBRACE},
    {"BACKSLASH", KEY_BACKSLASH},
    {"SEMICOLON", KEY_SEMICOLON},
    {"RIGHTBRACE", KEY_RIGHTBRACE},
    {"APOSTROPHE", KEY_APOSTROPHE},

    {"TAB", KEY_TAB},
    {"SPACE", KEY_SPACE},
    {"ENTER", KEY_ENTER},
    {"BACKSPACE", KEY_BACKSPACE},

    {"UP", KEY_UP},
    {"DOWN", KEY_DOWN},
    {"LEFT", KEY_LEFT},
    {"RIGHT", KEY_RIGHT},

    {"F1", KEY_F1},
    {"F2", KEY_F2},
    {"F3", KEY_F3},
    {"F4", KEY_F4},
    {"F5", KEY_F5},
    {"F6", KEY_F6},
    {"F7", KEY_F7},
    {"F8", KEY_F8},
    {"F9", KEY_F9},
    {"F10", KEY_F10},
    {"F11", KEY_F11},
    {"F12", KEY_F12},

    {"END", KEY_END},
    {"ESC", KEY_ESC},
    {"HOME", KEY_HOME},
    {"PRINT", KEY_PRINT},
    {"INSERT", KEY_INSERT},
    {"DELETE", KEY_DELETE},
    {"PAGEUP", KEY_PAGEUP},
    {"PAGEDOWN", KEY_PAGEDOWN},
};

KeyMap::KeyMap() {}

int KeyMap::get_key_code_from_name(std::string keyName)
{
    auto itterator = keyDefinitions.find(keyName);

    if (itterator == keyDefinitions.end())
        return -1;

    return itterator->second;
}
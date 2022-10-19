#ifndef KEY_MAP_H
#define KEY_MAP_H

#include <map>
#include <string>

class KeyMap
{
public:
    static int get_key_code_from_name(std::string keyName);

private:
    KeyMap();
    static std::map<std::string, int> keyDefinitions;
};

#endif // KEY_MAP_H
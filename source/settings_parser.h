#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <map>
#include <string>

class SettingsParser
{
public:
    SettingsParser();

    void load_defaults();
    bool settings_file_exists();
    std::map<std::string, std::string> read();

private:
    static const std::string help;

    std::string get_settings_directory();
    std::string get_settings_file_path();

    std::pair<std::string, std::string> split(const std::string &string);

};

#endif // INI_PARSER_H
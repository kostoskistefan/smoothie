#include "settings_parser.h"
#include "utilitites.h"
#include <sstream>
#include <fstream>
#include <sys/stat.h>

SettingsParser::SettingsParser() {}

std::string SettingsParser::get_settings_directory()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // TODO: Get "AppData" folder and save settings there
#elif defined(__linux__) || defined(__unix__)

    std::string home = std::getenv("HOME");

    if (home.empty())
        Utilities::exit_failure("Failed to get the $HOME environment variable\n");

    std::string settingsDirectory = home + "/.config/smoothie/";

    mkdir(settingsDirectory.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

    return settingsDirectory;

#endif
}

std::string SettingsParser::get_settings_file_path()
{
    return get_settings_directory() + "smoothie.cfg";
}

std::pair<std::string, std::string> SettingsParser::split(const std::string &string)
{
    std::pair<std::string, std::string> pair;

    int delimiterIndex = string.find_first_of('=');

    pair.first = string.substr(0, delimiterIndex);
    pair.second = string.substr(delimiterIndex + 1);

    Utilities::trim(pair.first);
    Utilities::trim(pair.second);

    return pair;
}

bool SettingsParser::settings_file_exists()
{
    if (FILE *file = fopen(get_settings_file_path().c_str(), "r"))
    {
        fclose(file);
        return true;
    }

    else
        return false;
}

std::map<std::string, std::string> SettingsParser::read()
{
    std::string settingsFilePath = get_settings_file_path();
    std::ifstream settingsFile(settingsFilePath);

    if (!settingsFile.is_open())
        Utilities::exit_failure("Failed to open settings file for reading");

    std::string line;
    std::map<std::string, std::string> settings;

    while (std::getline(settingsFile, line))
    {
        Utilities::trim(line);

        if (line.front() == '#' || line.front() == '[' || line.empty())
            continue;

        auto pair = split(line);

        settings[pair.first] = pair.second;
    }

    return settings;
}

void SettingsParser::load_defaults()
{
    std::stringstream ss;

    ss << "[Key Bindings]\n";
    
    ss << "Accelerate    = UP\n";
    ss << "Brake         = DOWN\n";
    ss << "Steer Left    = LEFT\n";
    ss << "Steer Right   = RIGHT\n";
    ss << "Action Key 1  = 1\n";
    ss << "Action Key 2  = 2\n";
    ss << "Action Key 3  = 3\n";
    ss << "Action Key 4  = 4\n";
    ss << "Action Key 5  = 5\n";
    ss << "Action Key 6  = 6\n";
    ss << "Action Key 7  = 7\n";
    ss << "Action Key 8  = 8\n";
    ss << "Action Key 9  = 9\n";
    ss << "Action Key 10 = 0\n\n";

    std::string settingsFilePath = get_settings_file_path();
    std::ofstream settingsFile(settingsFilePath, std::ios::out | std::ios::app);

    if (!settingsFile.is_open())
        Utilities::exit_failure("Failed to open settings file for writing");

    settingsFile << ss.str();
}

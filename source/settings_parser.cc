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

    ss << "[Smoothie Settings]\n";
    
    ss << "Accelerate    = W\n";
    ss << "Brake         = S\n";
    ss << "Steer Left    = A\n";
    ss << "Steer Right   = D\n";
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

    ss << this->help;

    std::string settingsFilePath = get_settings_file_path();
    std::ofstream settingsFile(settingsFilePath, std::ios::out | std::ios::app);

    if (!settingsFile.is_open())
        Utilities::exit_failure("Failed to open settings file for writing");

    settingsFile << ss.str();
}

const std::string SettingsParser::help =
    "# All lines that start with a \"#\" sign will be ignored\n#\n"
    "# Settings Format (The available actions and key codes are defined below): \n"
    "# \tACTION = KEY_CODE\n#\n"
    "# ACTION:\n"
    "# \tAccelerate   \n"
    "# \tBrake        \n"
    "# \tSteer Left   \n"
    "# \tSteer Right  \n"
    "# \tAction Key 1 \n"
    "# \tAction Key 2 \n"
    "# \tAction Key 3 \n"
    "# \tAction Key 4 \n"
    "# \tAction Key 5 \n"
    "# \tAction Key 6 \n"
    "# \tAction Key 7 \n"
    "# \tAction Key 8 \n"
    "# \tAction Key 9 \n"
    "# \tAction Key 10\n#\n"
    "# Keys:\n"
    "# \t+------------+-------------------+\n"
    "# \t|  KEY_CODE  |    Explanation    |\n"
    "# \t+------------+-------------------+\n"
    "# \t| A          | Key A             |\n"
    "# \t| B          | Key B             |\n"
    "# \t| C          | Key C             |\n"
    "# \t| D          | Key D             |\n"
    "# \t| E          | Key E             |\n"
    "# \t| F          | Key F             |\n"
    "# \t| G          | Key G             |\n"
    "# \t| H          | Key H             |\n"
    "# \t| I          | Key I             |\n"
    "# \t| J          | Key J             |\n"
    "# \t| K          | Key K             |\n"
    "# \t| L          | Key L             |\n"
    "# \t| M          | Key M             |\n"
    "# \t| N          | Key N             |\n"
    "# \t| O          | Key O             |\n"
    "# \t| P          | Key P             |\n"
    "# \t| Q          | Key Q             |\n"
    "# \t| R          | Key R             |\n"
    "# \t| S          | Key S             |\n"
    "# \t| T          | Key T             |\n"
    "# \t| U          | Key U             |\n"
    "# \t| V          | Key V             |\n"
    "# \t| W          | Key W             |\n"
    "# \t| X          | Key X             |\n"
    "# \t| Y          | Key Y             |\n"
    "# \t| Z          | Key Z             |\n"
    "# \t| 0          | Key 0             |\n"
    "# \t| 1          | Key 1             |\n"
    "# \t| 2          | Key 2             |\n"
    "# \t| 3          | Key 3             |\n"
    "# \t| 4          | Key 4             |\n"
    "# \t| 5          | Key 5             |\n"
    "# \t| 6          | Key 6             |\n"
    "# \t| 7          | Key 7             |\n"
    "# \t| 8          | Key 8             |\n"
    "# \t| 9          | Key 9             |\n"
    "# \t| KP0        | Keypad 0          |\n"
    "# \t| KP1        | Keypad 1          |\n"
    "# \t| KP2        | Keypad 2          |\n"
    "# \t| KP3        | Keypad 3          |\n"
    "# \t| KP4        | Keypad 4          |\n"
    "# \t| KP5        | Keypad 5          |\n"
    "# \t| KP6        | Keypad 6          |\n"
    "# \t| KP7        | Keypad 7          |\n"
    "# \t| KP8        | Keypad 8          |\n"
    "# \t| KP9        | Keypad 9          |\n"
    "# \t| KPDOT      | Keypad Dot        |\n"
    "# \t| KPPLUS     | Keypad Plus       |\n"
    "# \t| KPSLASH    | Keypad Slash      |\n"
    "# \t| KPMINUS    | Keypad Minus      |\n"
    "# \t| KPENTER    | Keypad Enter      |\n"
    "# \t| KPASTERISK | Keypad Asterisk   |\n"
    "# \t| DOT        | Key Dot           |\n"
    "# \t| COMMA      | Key Comma         |\n"
    "# \t| SLASH      | Key Forward Slash |\n"
    "# \t| MINUS      | Key Minus         |\n"
    "# \t| EQUAL      | Key Equal         |\n"
    "# \t| LEFTBRACE  | Key Left Brace    |\n"
    "# \t| BACKSLASH  | Key Back Slash    |\n"
    "# \t| SEMICOLON  | Key Semicolon     |\n"
    "# \t| RIGHTBRACE | Key Right Brace   |\n"
    "# \t| APOSTROPHE | Key Apostrophe    |\n"
    "# \t| TAB        | Key Tab           |\n"
    "# \t| SPACE      | Key Space         |\n"
    "# \t| ENTER      | Key Enter         |\n"
    "# \t| BACKSPACE  | Key Backspace     |\n"
    "# \t| UP         | Key Up Arrow      |\n"
    "# \t| DOWN       | Key Down Arrow    |\n"
    "# \t| LEFT       | Key Left Arrow    |\n"
    "# \t| RIGHT      | Key Right Arrow   |\n"
    "# \t| F1         | Key F1            |\n"
    "# \t| F2         | Key F2            |\n"
    "# \t| F3         | Key F3            |\n"
    "# \t| F4         | Key F4            |\n"
    "# \t| F5         | Key F5            |\n"
    "# \t| F6         | Key F6            |\n"
    "# \t| F7         | Key F7            |\n"
    "# \t| F8         | Key F8            |\n"
    "# \t| F9         | Key F9            |\n"
    "# \t| F10        | Key F10           |\n"
    "# \t| F11        | Key F11           |\n"
    "# \t| F12        | Key F12           |\n"
    "# \t| END        | Key End           |\n"
    "# \t| ESC        | Key Escape        |\n"
    "# \t| HOME       | Key Home          |\n"
    "# \t| PRINT      | Key Print         |\n"
    "# \t| INSERT     | Key Insert        |\n"
    "# \t| DELETE     | Key Delete        |\n"
    "# \t| PAGEUP     | Key Page Up       |\n"
    "# \t| PAGEDOWN   | Key Page Down     |\n"
    "# \t+------------+-------------------+\n";

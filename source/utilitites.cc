#include "utilitites.h"
#include <algorithm>

void Utilities::exit_failure(std::string message)
{
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

std::string Utilities::uppercase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}

void Utilities::trim(std::string &string)
{
    const char* t = " \t\n\r\f\v";

    string.erase(0, string.find_first_not_of(t));
    string.erase(string.find_last_not_of(t) + 1);
}
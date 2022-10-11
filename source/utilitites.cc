#include "utilitites.h"

void Utilities::exit_failure(std::string message)
{
    perror(message.c_str());
    exit(EXIT_FAILURE);
}
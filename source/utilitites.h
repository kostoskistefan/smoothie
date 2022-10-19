#ifndef UTILITITES_H
#define UTILITITES_H

#include <vector>
#include <string>

namespace Utilities
{
    void exit_failure(std::string message);
    
    void trim(std::string &string);
    std::string uppercase(std::string string);
}

#endif // UTILITITES_H
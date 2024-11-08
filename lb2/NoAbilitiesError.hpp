#ifndef NO_ABILITIES_ERROR_HPP
#define NO_ABILITIES_ERROR_HPP

#include "structures.hpp"

class NoAbilitiesError : public std::runtime_error
{
public:
    NoAbilitiesError(const std::string &msg) : std::runtime_error(msg) {}
};

#endif
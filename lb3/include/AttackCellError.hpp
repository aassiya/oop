#ifndef ATTACK_CELL_ERROR_HPP
#define ATTACK_CELL_ERROR_HPP

#include "structures.hpp"

class AttackCellError : public std::runtime_error
{
public:
    AttackCellError(const std::string &msg) : std::runtime_error(msg) {}
};

#endif
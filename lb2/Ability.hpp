#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "GameField.hpp"
#include "Structures.hpp"

class Ability
{
public:
    virtual ~Ability() = default;
    virtual AbilityStatus apply(GameField &gameField) = 0;
    virtual std::string getName() const = 0;
};

#endif
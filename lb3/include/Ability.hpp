#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "GameField.hpp"
#include "Structures.hpp"
#include <tuple>

class Ability
{
public:
    virtual ~Ability() = default;
    virtual std::tuple<bool, AbilityStatus> apply(GameField &gameField) = 0;
    virtual std::string getName() const = 0;
};

#endif
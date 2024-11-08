#ifndef SHELLING_ABILITY_HPP
#define SHELLING_ABILITY_HPP

#include "Ability.hpp"
#include "AbilityManager.hpp"

class ShellingAbility : public Ability
{
public:
    AbilityStatus apply(GameField &gameField);
    std::string getName() const;
};

#endif
#ifndef SHELLING_ABILITY_HPP
#define SHELLING_ABILITY_HPP

#include "Ability.hpp"

class ShellingAbility : public Ability
{
public:
    std::tuple<bool, AbilityStatus> apply(GameField &gameField);
    std::string getName() const;
};

#endif
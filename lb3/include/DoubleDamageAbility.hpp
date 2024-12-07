#ifndef DOUBLE_DAMAGE_ABILITY_HPP
#define DOUBLE_DAMAGE_ABILITY_HPP

#include "Ability.hpp"

class DoubleDamageAbility : public Ability
{
public:
    std::tuple<bool, AbilityStatus> apply(GameField &gameField) override;
    std::string getName() const override;
};

#endif
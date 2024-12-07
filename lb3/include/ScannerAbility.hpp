#ifndef SCANNER_ABILITY_HPP
#define SCANNER_ABILITY_HPP

#include "Ability.hpp"

class ScannerAbility : public Ability
{
public:
    std::tuple<bool, AbilityStatus> apply(GameField &gameField) override;
    std::string getName() const;
};

#endif
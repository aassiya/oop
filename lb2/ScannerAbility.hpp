#ifndef SCANNER_ABILITY_HPP
#define SCANNER_ABILITY_HPP

#include "Ability.hpp"
#include "AbilityManager.hpp"

class ScannerAbility : public Ability
{
public:
    AbilityStatus apply(GameField &gameField) override;
    std::string getName() const;
};

#endif
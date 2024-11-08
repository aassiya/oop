#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP

#include <queue>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

#include "Ability.hpp"
#include "NoAbilitiesError.hpp"

class AbilityManager
{
public:
    AbilityManager();

    AbilityStatus useAbility(GameField &gameField);
    void addRandomAbility();
    void shipWasDestroyed();

private:
    std::queue<std::unique_ptr<Ability>> abilities;
};

#endif
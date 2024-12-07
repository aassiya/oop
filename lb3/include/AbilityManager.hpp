#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP

#include <queue>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

#include "Ability.hpp"
#include "NoAbilitiesError.hpp"
#include "DoubleDamageAbility.hpp"
#include "ScannerAbility.hpp"
#include "ShellingAbility.hpp"

#include <json.hpp>
using json = nlohmann::json;

class AbilityManager
{
public:
    AbilityManager();
    ~AbilityManager();

    std::tuple<bool, AbilityStatus> useAbility(GameField &gameField);
    void addRandomAbility();
    void shipWasDestroyed();

    json saveToJson() const;
    AbilityManager loadFromJson(const json &j, GameField &gameField);

private:
    std::queue<std::shared_ptr<Ability>> abilities;
};

#endif
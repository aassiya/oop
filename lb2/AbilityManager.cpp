#include "AbilityManager.hpp"
#include "DoubleDamageAbility.hpp"
#include "ScannerAbility.hpp"
#include "ShellingAbility.hpp"

AbilityManager::AbilityManager()
{
    std::vector<std::unique_ptr<Ability>> setAbilities;
    setAbilities.push_back(std::make_unique<DoubleDamageAbility>());
    setAbilities.push_back(std::make_unique<ScannerAbility>());
    setAbilities.push_back(std::make_unique<ShellingAbility>());

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::shuffle(setAbilities.begin(), setAbilities.end(), rng);

    for (auto &ability : setAbilities)
    {
        abilities.push(std::move(ability));
    }
}

AbilityStatus AbilityManager::useAbility(GameField &gameField)
{
    if (abilities.empty())
    {
        throw NoAbilitiesError("No abilities available\n");
    }

    auto ability = std::move(abilities.front());
    abilities.pop();
    std::cout << "Using " << ability->getName() << std::endl;
    return ability->apply(gameField);
}

void AbilityManager::addRandomAbility()
{
    int abilityType = std::rand() % 3;

    switch (abilityType)
    {
    case 0:
        abilities.push(std::make_unique<DoubleDamageAbility>());
        break;
    case 1:
        abilities.push(std::make_unique<ScannerAbility>());
        break;
    case 2:
        abilities.push(std::make_unique<ShellingAbility>());
        break;
    }
}

void AbilityManager::shipWasDestroyed()
{
    addRandomAbility();
}
#include "AbilityManager.hpp"

AbilityManager::AbilityManager()
{
    std::vector<std::shared_ptr<Ability>> setAbilities;
    setAbilities.push_back(std::make_shared<DoubleDamageAbility>());
    setAbilities.push_back(std::make_shared<ScannerAbility>());
    setAbilities.push_back(std::make_shared<ShellingAbility>());

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::shuffle(setAbilities.begin(), setAbilities.end(), rng);

    for (auto &ability : setAbilities)
    {
        abilities.push(std::move(ability));
    }
}

AbilityManager::~AbilityManager() {}

std::tuple<bool, AbilityStatus> AbilityManager::useAbility(GameField &gameField)
{
    if (abilities.empty())
    {
        throw NoAbilitiesError("No abilities available\n");
    }

    auto ability = abilities.front();
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
        abilities.push(std::make_shared<DoubleDamageAbility>());
        break;
    case 1:
        abilities.push(std::make_shared<ScannerAbility>());
        break;
    case 2:
        abilities.push(std::make_shared<ShellingAbility>());
        break;
    }
}

void AbilityManager::shipWasDestroyed()
{
    addRandomAbility();
}

json AbilityManager::saveToJson() const
{
    json j;
    j["abilities"] = json::array();
    auto tempQueue = abilities;
    while (!tempQueue.empty())
    {
        auto ability = tempQueue.front();
        j["abilities"].push_back(ability->getName());
        tempQueue.pop();
    }
    return j;
}

AbilityManager AbilityManager::loadFromJson(const json &j, GameField &gameField)
{
    AbilityManager manager;

    for (const auto &abilityName : j["abilities"])
    {
        std::shared_ptr<Ability> ability = nullptr;

        if (abilityName == "Double Damage Ability")
        {
            ability = std::make_shared<DoubleDamageAbility>();
        }
        else if (abilityName == "Scanner Ability")
        {
            ability = std::make_shared<ScannerAbility>();
        }
        else if (abilityName == "Shelling Ability")
        {
            ability = std::make_shared<ShellingAbility>();
        }
        else
        {
            throw std::runtime_error("Unknown ability name in JSON");
        }

        manager.abilities.push(ability);
    }

    return manager;
}
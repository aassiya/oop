#include "ShellingAbility.hpp"

AbilityStatus ShellingAbility::apply(GameField &gameField)
{
    while (true)
    {
        int rand_x = std::rand() % gameField.getColumns();
        int rand_y = std::rand() % gameField.getRows();
        if (gameField.shipInCell(rand_x, rand_y))
        {
            gameField.attackCell(rand_x, rand_y, 1);
            break;
        }
        else
        {
            continue;
        }
    }
    return AbilityStatus::SUCCESS;
}

std::string ShellingAbility::getName() const
{
    return "Shelling Ability";
}
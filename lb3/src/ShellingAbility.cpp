#include "ShellingAbility.hpp"

std::tuple<bool, AbilityStatus> ShellingAbility::apply(GameField &gameField)
{
    while (true)
    {
        int rand_x = std::rand() % gameField.getColumns();
        int rand_y = std::rand() % gameField.getRows();
        if (gameField.shipInCell(rand_x, rand_y) && gameField.getShipSegmentState(rand_x, rand_y) != SegmentState::DESTROYED)
        {
            bool attackResult = gameField.attackCell(rand_x, rand_y, 1);
            return {attackResult, AbilityStatus::SUCCESS};
        }
        else
        {
            continue;
        }
    }
}

std::string ShellingAbility::getName() const
{
    return "Shelling Ability";
}
#include "DoubleDamageAbility.hpp"

std::tuple<bool, AbilityStatus> DoubleDamageAbility::apply(GameField &gameField)
{
    int x, y;
    while (true)
    {
        std::cout << "Enter coordinates to double attack (x y):\n";
        std::cin >> x >> y;
        try
        {
            if (!gameField.isValidCoordinate(x, y) || gameField.getCellState(x, y) == CellState::EMPTY || (gameField.getCellState(x, y) == CellState::SHIP && gameField.getShipSegmentState(x, y) == SegmentState::DESTROYED))
            {
                throw std::out_of_range("Error: Invalid coordinates for double damage attack\n");
            }
            bool attackResult = gameField.attackCell(x, y, 2);
            if (gameField.shipInCell(x, y) && gameField.getShipSegmentState(x, y) == SegmentState::DESTROYED)
            {
                return {attackResult, AbilityStatus::DESTROYED};
            }
            return {attackResult, AbilityStatus::NOT_DESTROYED};
        }
        catch (const std::out_of_range &e)
        {
            std::cout << e.what() << "Try again\n"
                      << std::endl;
        }
    }
}

std::string DoubleDamageAbility::getName() const
{
    return "Double Damage Ability";
}
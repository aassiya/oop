#include "ScannerAbility.hpp"

AbilityStatus ScannerAbility::apply(GameField &gameField)
{
    int x, y;
    while (true) {
        std::cout << "Enter coordinates to scan the area around (x y):\n";
        std::cin >> x >> y;
        try
        {
            if (!gameField.isValidCoordinate(x, y))
            {
                throw std::out_of_range("Error: Invalid coordinates for scanning area\n");
            }
            bool flag = false;
            for (int dx = 0; dx < 2; ++dx)
            {
                for (int dy = 0; dy < 2; ++dy)
                {
                    if (gameField.shipInCell(x + dx, y + dy))
                    {
                        flag = true;
                    }
                }
            }
            if (flag)
            {
                return AbilityStatus::SHIP;
            }
            return AbilityStatus::EMPTY;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << e.what() << "Try again\n" << std::endl;
        }
    }
}

std::string ScannerAbility::getName() const
{
    return "Scanner Ability";
}
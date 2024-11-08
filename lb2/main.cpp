#include <iostream>
#include <limits>
#include <sstream>

#include "Ship.hpp"
#include "ShipsManager.hpp"
#include "GameField.hpp"
#include "Ability.hpp"
#include "AbilityManager.hpp"
#include "NoAbilitiesError.hpp"

int main()
{
    int rows, columns, numShips, currentLength;
    bool set = false;
    while (!set)
    {
        std::cout << "Enter number of rows: ";
        std::cin >> rows;
        if (rows <= 0)
        {
            std::cout << "Error: Invalid number of rows, try again" << std::endl;
            continue;
        }
        set = true;
    }
    set = false;
    while (!set)
    {
        std::cout << "Enter number of columns: ";
        std::cin >> columns;
        if (columns <= 0)
        {
            std::cout << "Error: Invalid number of columns, try again" << std::endl;
            continue;
        }
        set = true;
    }
    set = false;
    while (!set)
    {
        std::cout << "Enter number of ships: ";
        std::cin >> numShips;
        if (numShips <= 0)
        {
            std::cout << "Error: Invalid number of ships, try again" << std::endl;
            continue;
        }
        set = true;
    }
    std::vector<int> ships;
    for (int i = 0; i < numShips; i++)
    {
        bool set = false;
        while (!set)
        {
            std::cout << "Enter length of ship " << i + 1 << ": ";
            std::cin >> currentLength;
            if (currentLength < 1 || currentLength > 4)
            {
                std::cout << "Error: Invalid coordinate, try again" << std::endl;
                continue;
            }
            ships.push_back(currentLength);
            set = true;
        }
    }
    GameField gameField(rows, columns);
    ShipsManager shipsManager(ships);
    AbilityManager abilityManager;

    int orientation, x, y;
    for (size_t i = 0; i < shipsManager.getNumberOfShips(); i++)
    {
        bool placed = false;
        while (!placed)
        {
            try
            {
                gameField.printField();
                std::cout << "Enter orientation of ship " << i + 1 << " (1 - vertical, 0 - horizontal): ";
                std::cin >> orientation;
                std::cout << "Enter coordinates of ship " << i + 1 << ": ";
                std::cin >> x >> y;
                gameField.placeShip(shipsManager.getShip(i), orientation, x, y);
                placed = true;
            }
            catch (PlaceShipError &e)
            {
                std::cout << e.what() << "Try again" << std::endl;
            }
        }
    }
    gameField.printField();
    std::cout << "Enter 'ability' to use a special ability, '-' to attack, or 'end' to finish the game\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Your turn: \n";

        std::string input;
        std::getline(std::cin, input);

        if (input == "end")
        {
            std::cout << "The game is over";
            break;
        }
        else if (input == "ability")
        {
            AbilityStatus abilityStatus;
            try
            {
                abilityStatus = abilityManager.useAbility(gameField);
                std::cout << "Using ability result: " << abilityStatus << std::endl;
            }
            catch (NoAbilitiesError &e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }

            gameField.printField();
            if (abilityStatus != AbilityStatus::DESTROYED && abilityStatus != AbilityStatus::NOT_DESTROYED)
            {
                bool attacked = false;
                while (!attacked)
                {
                    try
                    {
                        int x, y;
                        std::cout << "Enter coordinates to attack (x y):" << std::endl;
                        std::cin >> x >> y;
                        bool attackResult = gameField.attackCell(x, y, 1);
                        if (attackResult)
                        {
                            std::cout << "You have received a new ability!\n";
                            abilityManager.shipWasDestroyed();
                        }
                        attacked = true;
                    }
                    catch (AttackCellError &e)
                    {
                        std::cout << e.what() << "Try again\n" << std::endl;
                    }
                }
            }
        }
        else if (input == "-")
        {
            bool attacked = false;
            while (!attacked)
            {
                try
                {
                    int x, y;
                    std::cout << "Enter coordinates to attack (x y):" << std::endl;
                    std::cin >> x >> y;
                    bool attackResult = gameField.attackCell(x, y, 1);
                    if (attackResult)
                    {
                        std::cout << "You have received a new ability!\n";
                        abilityManager.shipWasDestroyed();
                    }
                    attacked = true;
                }
                catch (AttackCellError &e)
                {
                    std::cout << e.what() << "Try again\n" << std::endl;
                }
            }
        } else {
            std::cout << "Error: Invalid input, try again" << std::endl;
            continue;
        }
        gameField.printField();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}
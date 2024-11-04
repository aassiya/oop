#include "gamecontroller.h"

GameController::GameController(int rows, int columns, const std::vector<int> &shipSizes)
    : playerField(rows, columns, shipSizes), shipsManager(shipSizes) {}

void GameController::startGame()
{
    try
    {
        int orientation, x, y;
        for (size_t i = 0; i < shipsManager.getNumberOfShips(); i++)
        {
            std::cout << "Enter orientation of ship " << i + 1 << " (1 - vertical, 0 - horizontal): ";
            std::cin >> orientation;
            std::cout << "Enter coordinates of ship " << i + 1 << ": ";
            std::cin >> x >> y;
            playerField.placeShip(i, orientation, x, y);
        }
        playerField.printYourField();
        int flag;
        while (true)
        {
            std::cout << "Do you want to continue the game? (1 - yes, 0 - no) ";
            std::cin >> flag;
            if (flag)
            {
                std::cout << "Enter coordinates of attack: ";
                std::cin >> x >> y;
                playerField.attack({x, y});
            }
            else
            {
                break;
            }
        }
        playerField.printYourField();
    }
    catch (const std::invalid_argument &ia)
    {
        std::cerr << "Argument error: " << ia.what() << std::endl;
    }
    catch (const std::out_of_range &oor)
    {
        std::cerr << "Range Error: " << oor.what() << std::endl;
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "Logical error: " << le.what() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Unknown error: " << ex.what() << std::endl;
    }
}

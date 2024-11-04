#include "gamecontroller.h"

int main()
{
    int rows, columns, numShips, currentLength;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> columns;
    std::cout << "Enter number of ships: ";
    std::cin >> numShips;
    std::vector<int> ships;
    for (int i = 0; i < numShips; i++) {
        std::cout << "Enter length of ship " << i + 1 << ": ";
        std::cin >> currentLength;
        ships.push_back(currentLength);
    }
    GameController gameController(rows, columns, ships);
    gameController.startGame();
    return 0;
}
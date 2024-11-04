#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamefield.h"

class GameController
{
public:
    GameController(int rows, int columns, const std::vector<int> &shipSizes);
    ~GameController() = default;

    void startGame();

private:
    GameField playerField;
    ShipsManager shipsManager;
};

#endif

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "shipsmanager.h"

class GameField
{
public:
    GameField(int rows, int columns, const std::vector<int> &shipSizes);
    GameField(const GameField &other);
    GameField(GameField &&other) noexcept;
    GameField &operator=(const GameField &other);
    GameField &operator=(GameField &&other) noexcept;
    ~GameField();

    void placeShip(int shipIndex, bool isVertical, int x, int y);
    void attack(const Coordinate &coord);
    CellStatus getCellStatus(int x, int y) const;
    void printField() const;
    void printYourField() const;

private:
    int rows;
    int columns;
    std::vector<std::vector<CellStatus>> field;
    ShipsManager shipsManager;

    bool isValidCoordinate(int x, int y) const;
    bool shipsAreTouching(const Coordinate &coord) const;
};

#endif
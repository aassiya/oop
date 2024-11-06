#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "ship.h"

enum class CellState
{
    UNKNOWN,
    EMPTY,
    SHIP
};

std::ostream &operator<<(std::ostream &os, const CellState &state);

class GameField
{
public:
    GameField(int rows, int columns);
    GameField(const GameField &other);
    GameField(GameField &&other);
    GameField &operator=(const GameField &other);
    GameField &operator=(GameField &&other);
    ~GameField();

    bool isValidCoordinate(int x, int y) const;
    bool shipsAreTouching(Ship *ship, bool isVertical, int x, int y) const;

    int getRows() const;
    int getColumns() const;
    bool shipInCell(int x, int y) const;
    CellState getCellState(int x, int y) const;
    SegmentState getShipSegmentState(int x, int y) const;

    void placeShip(Ship *ship, bool isVertical, int x, int y);
    void attackCell(int x, int y);

    void printField() const;

private:
    class Cell
    {
    public:
        Cell();
        ~Cell();

        bool isShip() const;
        void setState(CellState state);
        CellState getState() const;
        void setShipSegment(Ship *ship, int index);
        int getSegmentIndex() const;
        SegmentState getShipSegmentState() const;
        void attackCell();
        Ship *getShip() const;

    private:
        CellState state_;
        Ship *ship_;
        int segmentIndex;
    };

    int rows;
    int columns;
    std::vector<std::vector<Cell>> field;
};

#endif
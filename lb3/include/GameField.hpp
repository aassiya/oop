#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include <cstdlib>
#include <ctime>

#include "Ship.hpp"
#include "Structures.hpp"
#include "PlaceShipError.hpp"
#include "AttackCellError.hpp"

#include <json.hpp>
using json = nlohmann::json;

class GameField
{
public:
    GameField();
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
    void placeShipsRandomly(std::vector<int> ships);
    bool attackCell(int x, int y, int damage); // damage = 1 - обычная атака, damage = 2 - двойная атака

    void printField() const;
    void printEnemyField() const;

    json saveToJson() const;
    void loadFromJson(const json &j);
    std::pair<int, int> fromJsonSize(const json &j);

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
        void attackCell(int damage);
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
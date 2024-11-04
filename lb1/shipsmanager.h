#ifndef SHIPSMANAGER_H
#define SHIPSMANAGER_H

#include "ship.h"

class ShipsManager
{
public:
    ShipsManager(const std::vector<int> &shipSizes);
    ~ShipsManager();

    void addShip(int shipIndex, bool isVertical, int x, int y);
    size_t getNumberOfShips() const;
    int getShipLength(int shipIndex);
    void applyShipDamage(const Coordinate &coord);
    bool isShipAt(const Coordinate &coord) const;
    SegmentState getSegmentState(const Coordinate &coord) const;

private:
    std::vector<Ship> ships;
};

#endif
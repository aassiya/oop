#ifndef SHIPS_MANAGER_HPP
#define SHIPS_MANAGER_HPP

#include "Ship.hpp"

class ShipsManager
{
public:
    ShipsManager(const std::vector<int> &shipsSizes);
    ~ShipsManager();

    void addShip(int length, bool isVertical);
    void addShip(const Ship &ship);
    size_t getNumberOfShips() const;
    Ship *getShip(int index);
    std::vector<Ship *> getShips() const;
    void applyShipDamage(int ShipIndex, int SegmentIndex);

private:
    std::vector<Ship> ships;
};

#endif
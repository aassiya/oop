#ifndef SHIPS_MANAGER_HPP
#define SHIPS_MANAGER_HPP

#include "Ship.hpp"

#include <json.hpp>
using json = nlohmann::json;

class ShipsManager
{
public:
    ShipsManager();
    ShipsManager(const std::vector<int> &shipsSizes);
    ~ShipsManager();

    void addShip(int length, bool isVertical);
    void addShip(const Ship &ship);
    size_t getNumberOfShips() const;
    Ship *getShip(int index);
    std::vector<Ship *> getShips() const;
    void applyShipDamage(int ShipIndex, int SegmentIndex);
    json saveToJson() const;
    ShipsManager* loadFromJson(const json &j);

private:
    std::vector<Ship> ships;
};

#endif
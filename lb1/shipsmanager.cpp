#include "shipsmanager.h"

ShipsManager::ShipsManager(const std::vector<int> &shipSizes)
{
    for (size_t i = 0; i < shipSizes.size(); i++)
    {
        if (shipSizes[i] < 1 || shipSizes[i] > 4)
        {
            throw std::invalid_argument("Length of the ship must be between 1 and 4.");
        }
        ships.emplace_back(shipSizes[i], true, -1, -1);
    }
}

ShipsManager::~ShipsManager() {}

void ShipsManager::addShip(int shipIndex, bool isVertical, int x, int y)
{
    if (shipIndex < 0 || shipIndex >= this->getNumberOfShips())
    {
        throw std::out_of_range("Ship index out of range.");
    }
    ships[shipIndex] = Ship(ships[shipIndex].getLength(), isVertical, x, y);
}

size_t ShipsManager::getNumberOfShips() const
{
    return ships.size();
}

int ShipsManager::getShipLength(int shipIndex)
{
    if (shipIndex < 0 || shipIndex >= this->getNumberOfShips())
    {
        throw std::out_of_range("Ship index out of range.");
    }
    return ships[shipIndex].getLength();
}

void ShipsManager::applyShipDamage(const Coordinate &coord)
{
    for (auto &ship : ships)
    {
        for (size_t i = 0; i < ship.getLength(); i++)
        {
            if (ship.getCoordinates(i) == coord)
            {
                ship.applySegmentDamage(i);
            }
        }
    }
}

bool ShipsManager::isShipAt(const Coordinate &coord) const
{
    for (const auto &ship : ships)
    {
        for (size_t i = 0; i < ship.getLength(); i++)
        {
            if (ship.getCoordinates(i) == coord)
            {
                return true;
            }
        }
    }
    return false;
}

SegmentState ShipsManager::getSegmentState(const Coordinate &coord) const
{
    for (const auto &ship : ships)
    {
        for (size_t i = 0; i < ship.getLength(); i++)
        {
            if (ship.getCoordinates(i) == coord)
            {
                return ship.getSegmentState(i);
            }
        }
    }
    return SegmentState::UNKNOWN;
}

#include "ShipsManager.hpp"

ShipsManager::ShipsManager(const std::vector<int> &shipsSizes)
{
    for (size_t i = 0; i < shipsSizes.size(); i++)
    {
        if (shipsSizes[i] < 1 || shipsSizes[i] > 4)
        {
            throw std::invalid_argument("Length of the ship must be between 1 and 4.");
        }
        ships.emplace_back(shipsSizes[i], true);
    }
}

ShipsManager::~ShipsManager() {}

void ShipsManager::addShip(int length, bool isVertical)
{
    ships.emplace_back(length, isVertical);
}

void ShipsManager::addShip(const Ship &ship)
{
    ships.emplace_back(ship);
}

size_t ShipsManager::getNumberOfShips() const
{
    return ships.size();
}

Ship *ShipsManager::getShip(int shipIndex)
{
    if (shipIndex < 0 || shipIndex >= this->getNumberOfShips())
    {
        throw std::out_of_range("Ship index out of range.");
    }
    return &ships[shipIndex];
}

std::vector<Ship *> ShipsManager::getShips() const
{
    std::vector<Ship *> shipPtrs;
    for (auto &ship : ships)
    {
        shipPtrs.push_back(const_cast<Ship *>(&ship));
    }
    return shipPtrs;
}

void ShipsManager::applyShipDamage(int shipIndex, int segmentIndex)
{
    if (shipIndex < 0 || shipIndex >= this->getNumberOfShips())
    {
        throw std::out_of_range("Ship index out of range.");
    }
    ships[shipIndex].applySegmentDamage(segmentIndex, 1);
}

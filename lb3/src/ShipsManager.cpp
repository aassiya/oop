#include "ShipsManager.hpp"

ShipsManager::ShipsManager() {}

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

json ShipsManager::saveToJson() const
{
    json j;
    j["ships"] = json::array();
    for (const auto &ship : ships)
    {
        json shipJson;
        shipJson["length"] = ship.getLength();
        shipJson["isVertical"] = ship.getOrientation();
        shipJson["segments"] = json::array();
        for (int i = 0; i < ship.getLength(); ++i)
        {
            shipJson["segments"].push_back(static_cast<int>(ship.getSegmentState(i)));
        }
        j["ships"].push_back(shipJson);
    }
    return j;
}

ShipsManager *ShipsManager::loadFromJson(const json &j)
{
    ShipsManager *manager = new ShipsManager();
    for (const auto &shipJson : j["ships"])
    {
        int length = shipJson["length"];
        bool isVertical = shipJson["isVertical"];
        Ship ship(length, isVertical);
        const auto &segments = shipJson["segments"];
        for (size_t i = 0; i < segments.size(); ++i)
        {
            SegmentState state = static_cast<SegmentState>(segments[i].get<int>());
            if (state == SegmentState::DAMAGED)
            {
                ship.applySegmentDamage(i, 1);
            }
            else if (state == SegmentState::DESTROYED)
            {
                ship.applySegmentDamage(i, 2);
            }
        }
        manager->addShip(ship);
    }
    return manager;
}

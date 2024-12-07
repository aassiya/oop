#ifndef PLACE_SHIP_ERROR_HPP
#define PLACE_SHIP_ERROR_HPP

#include "structures.hpp"

class PlaceShipError : public std::runtime_error
{
public:
    PlaceShipError(const std::string &msg) : std::runtime_error(msg) {}
};

#endif
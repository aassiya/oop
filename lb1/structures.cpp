#include "structures.h"

bool Coordinate::operator==(const Coordinate &other) const
{
    return x == other.x && y == other.y;
}

ShipSegment::ShipSegment(int x, int y) : coordinates({x, y}), state(SegmentState::UNHARMED) {};
ShipSegment::ShipSegment() : coordinates({-1, -1}), state(SegmentState::UNHARMED) {};

std::ostream& operator<<(std::ostream &os, const Coordinate &coord)
{
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;
}
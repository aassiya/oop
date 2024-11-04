#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>

enum class SegmentState
{
    UNHARMED,
    DAMAGED,
    DESTROYED,
    UNKNOWN
};

enum class CellStatus
{
    UNKNOWN,
    EMPTY,
    SHIP
};

struct Coordinate
{
    int x;
    int y;

    bool operator==(const Coordinate &other) const;
};

struct ShipSegment
{
    Coordinate coordinates;
    SegmentState state;
    ShipSegment(int x, int y);
    ShipSegment();
};

std::ostream &operator<<(std::ostream &os, const Coordinate &coord);

#endif
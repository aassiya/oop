#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <iostream>
#include <vector>

enum class SegmentState
{
    UNHARMED,
    DAMAGED,
    DESTROYED,
};

enum class CellState
{
    UNKNOWN,
    EMPTY,
    SHIP
};

enum class AbilityStatus
{
    DESTROYED,
    NOT_DESTROYED,
    SHIP,
    EMPTY,
    SUCCESS
};

std::ostream &operator<<(std::ostream &os, const SegmentState &state);
std::ostream &operator<<(std::ostream &os, const CellState &state);
std::ostream &operator<<(std::ostream &os, const AbilityStatus &status);

#endif
#include "Structures.hpp"

std::ostream &operator<<(std::ostream &os, const SegmentState &state)
{
    switch (state)
    {
    case SegmentState::UNHARMED:
        os << "Unharmed";
        break;
    case SegmentState::DAMAGED:
        os << "Damaged";
        break;
    case SegmentState::DESTROYED:
        os << "Destroyed";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const CellState &state)
{
    switch (state)
    {
    case CellState::EMPTY:
        os << "Empty";
        break;
    case CellState::SHIP:
        os << "Ship";
        break;
    case CellState::UNKNOWN:
        os << "Unknown";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const AbilityStatus &status)
{
    switch (status)
    {
    case AbilityStatus::DESTROYED:
        os << "DESTROYED";
        break;
    case AbilityStatus::NOT_DESTROYED:
        os << "NOT_DESTROYED";
        break;
    case AbilityStatus::SHIP:
        os << "SHIP";
        break;
    case AbilityStatus::EMPTY:
        os << "EMPTY";
        break;
    case AbilityStatus::SUCCESS:
        os << "SUCCESS";
        break;
    }
    return os;
}

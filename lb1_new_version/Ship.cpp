#include "Ship.h"

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
        return os;
    }
    return os;
}

Ship::Ship(int length, bool isVertical) : length(length), isVertical(isVertical), segments(length, SegmentState::UNHARMED)
{
    if (length < 1 || length > 4)
    {
        throw std::invalid_argument("Length of the ship must be between 1 and 4.");
    }
}

Ship::~Ship() {}

SegmentState Ship::getSegmentState(int segmentIndex) const
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[segmentIndex];
}

bool Ship::getOrientation() const
{
    return isVertical;
}

int Ship::getLength() const
{
    return length;
}

void Ship::applySegmentDamage(int segmentIndex)
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    if (segments[segmentIndex] == SegmentState::UNHARMED)
    {
        segments[segmentIndex] = SegmentState::DAMAGED;
    }
    else if (segments[segmentIndex] == SegmentState::DAMAGED)
    {
        segments[segmentIndex] = SegmentState::DESTROYED;
    }
}

bool Ship::isDestroyed() const
{
    for (int i = 0; i < length; i++)
    {
        if (segments[i] != SegmentState::DESTROYED)
        {
            return false;
        }
    }
    return true;
}

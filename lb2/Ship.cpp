#include "Ship.hpp"

Ship::Ship(int length, bool isVertical) : length(length), isVertical(isVertical), segments(length, SegmentState::UNHARMED)
{
    if (length < 1 || length > 4)
    {
        throw std::invalid_argument("Length of the ship must be between 1 and 4.");
    }
}

Ship::~Ship() {}

int Ship::getLength() const
{
    return length;
}

bool Ship::getOrientation() const
{
    return isVertical;
}

SegmentState Ship::getSegmentState(int segmentIndex) const
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[segmentIndex];
}

void Ship::applySegmentDamage(int segmentIndex, int damage)
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    if (damage == 1) {
        if (segments[segmentIndex] == SegmentState::UNHARMED)
        {
            segments[segmentIndex] = SegmentState::DAMAGED;
        }
        else if (segments[segmentIndex] == SegmentState::DAMAGED)
        {
            segments[segmentIndex] = SegmentState::DESTROYED;
        }
    } else {
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

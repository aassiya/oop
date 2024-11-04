#include "ship.h"

Ship::Ship(int length, bool isVertical, int x, int y) : length(length), isVertical(isVertical)
{
    if (length < 1 || length > 4)
    {
        throw std::invalid_argument("Length of the ship must be between 1 and 4.");
    }
    segments.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        if (isVertical)
        {
            segments.emplace_back(x, y + i);
        }
        else
        {
            segments.emplace_back(x + i, y);
        }
    }
}

Ship::~Ship() {}

SegmentState Ship::getSegmentState(int segmentIndex) const
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[segmentIndex].state;
}

Coordinate Ship::getCoordinates(int segmentIndex) const
{
    if (segmentIndex < 0 || segmentIndex >= length)
    {
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[segmentIndex].coordinates;
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
    if (segments[segmentIndex].state == SegmentState::UNHARMED)
    {
        segments[segmentIndex].state = SegmentState::DAMAGED;
    }
    else if (segments[segmentIndex].state == SegmentState::DAMAGED)
    {
        segments[segmentIndex].state = SegmentState::DESTROYED;
    }
}

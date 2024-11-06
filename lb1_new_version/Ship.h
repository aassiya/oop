#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>

enum class SegmentState
{
    UNHARMED,
    DAMAGED,
    DESTROYED,
};

std::ostream &operator<<(std::ostream &os, const SegmentState &state);

class Ship
{
public:
    // Ship(int length, bool isVertical, int x, int y);
    Ship(int length, bool isVertical);
    ~Ship();

    SegmentState getSegmentState(int segmentIndex) const;
    // Coordinate getCoordinates(int segmentIndex) const;
    bool getOrientation() const;
    int getLength() const;
    void applySegmentDamage(int segmentIndex);
    bool isDestroyed() const;

private:
    int length;
    bool isVertical;
    std::vector<SegmentState> segments;
};

#endif
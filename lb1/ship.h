#ifndef SHIP_H
#define SHIP_H

#include "structures.h"

class Ship
{
public:
    Ship(int length, bool isVertical, int x, int y);
    ~Ship();

    SegmentState getSegmentState(int segmentIndex) const;
    Coordinate getCoordinates(int segmentIndex) const;
    bool getOrientation() const;
    int getLength() const;
    void applySegmentDamage(int segmentIndex);

private:
    int length;
    bool isVertical;
    std::vector<ShipSegment> segments;
};

#endif
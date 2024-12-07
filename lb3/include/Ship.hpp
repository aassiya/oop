#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <vector>

#include "Structures.hpp"

class Ship
{
public:
    Ship(int length, bool isVertical);
    ~Ship();

    int getLength() const;
    bool getOrientation() const;
    SegmentState getSegmentState(int segmentIndex) const;
    void applySegmentDamage(int segmentIndex, int damage);
    bool isDestroyed() const;

private:
    int length;
    bool isVertical;
    std::vector<SegmentState> segments;
};

#endif
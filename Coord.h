#pragma once

#include <vector>

struct Coord
{
    double x;
    double y;
};

struct Segment
{
    Coord a;
    Coord b;
};

using Bezier   = std::vector<Coord>;
using Segments = std::vector<Segment>;


Coord operator-(const Coord& coord);
Coord operator+(const Coord& coord1, const Coord& coord2);
Coord operator-(const Coord& coord1, const Coord& coord2);
Coord operator*(const Coord& coord, double factor);
Coord operator*(double factor, const Coord& coord);

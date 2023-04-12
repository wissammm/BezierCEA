#pragma once

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

Coord operator-(const Coord& coord);
Coord operator+(const Coord& coord1, const Coord& coord2);
Coord operator-(const Coord& coord1, const Coord& coord2);
Coord operator*(const Coord& coord, double factor);
Coord operator*(double factor, const Coord& coord);
Coord operator/(const Coord& coord, double factor);
Coord operator/(double factor, const Coord& coord);

#pragma once

#include <vector>

struct Coord
{
    double x;
    double y;
};

Coord computeTangent(Coord deriv_time_t);
Coord computeNormal(Coord tengent);

double norm(Coord a);
double abs(Coord a);

Coord operator-(const Coord& coord);
Coord operator+(const Coord& coord1, const Coord& coord2);
Coord operator-(const Coord& coord1, const Coord& coord2);
Coord operator*(const Coord& coord, double factor);
Coord operator*(double factor, const Coord& coord);
Coord operator/(const Coord& coord, double factor);
Coord operator/(double factor, const Coord& coord);

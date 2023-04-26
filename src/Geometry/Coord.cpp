#include "Coord.h"
#include <math.h>



double norm(Coord a) { return dot(a, a); }

double abs(Coord a) { return sqrt(norm(a)); }


Coord operator-(const Coord& coord) { return {-coord.x, -coord.y}; }
Coord operator+(const Coord& coord1, const Coord& coord2) { return {coord1.x + coord2.x, coord1.y + coord2.y}; }
Coord operator-(const Coord& coord1, const Coord& coord2) { return {coord1.x - coord2.x, coord1.y - coord2.y}; }
Coord operator*(const Coord& coord, double factor) { return {coord.x * factor, coord.y * factor}; }
Coord operator*(double factor, const Coord& coord) { return {factor * coord.x, factor * coord.y}; }
Coord operator/(const Coord& coord, double factor) { return {coord.x / factor, coord.y / factor}; }
Coord operator/(double factor, const Coord& coord) { return {factor / coord.x, factor / coord.y}; }

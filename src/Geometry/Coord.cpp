#include "Coord.h"
#include <math.h>

Coord computeTangent(Coord deriv_time_t) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(deriv_time_t.x * deriv_time_t.x + deriv_time_t.y * deriv_time_t.y);
    return Coord({deriv_time_t.x / m, deriv_time_t.y / m});
}

Coord computeNormal(Coord tengent) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(tengent.x * tengent.x + tengent.y * tengent.y);

    return Coord({-tengent.y / m, tengent.x / m});
}

Coord operator-(const Coord& coord) { return {-coord.x, -coord.y}; }
Coord operator+(const Coord& coord1, const Coord& coord2) { return {coord1.x + coord2.x, coord1.y + coord2.y}; }
Coord operator-(const Coord& coord1, const Coord& coord2) { return {coord1.x - coord2.x, coord1.y - coord2.y}; }
Coord operator*(const Coord& coord, double factor) { return {coord.x * factor, coord.y * factor}; }
Coord operator*(double factor, const Coord& coord) { return {factor * coord.x, factor * coord.y}; }
Coord operator/(const Coord& coord, double factor) { return {coord.x / factor, coord.y / factor}; }
Coord operator/(double factor, const Coord& coord) { return {factor / coord.x, factor / coord.y}; }

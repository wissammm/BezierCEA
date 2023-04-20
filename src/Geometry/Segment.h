#pragma once
#include "Coord.h"

struct Segment
{
    Coord a;
    Coord b;
};
double distance(Segment seg);
double distance(Coord A, Coord B);
double determinant(Coord a1, Coord a2, Coord b1, Coord b2);
Coord  getIntersectionPoint(Segment seg1, Segment seg2);
Coord  getIntersectionPoint(Coord a1, Coord a2, Coord b1, Coord b2);
bool   isOnSegment(Coord p, Coord a, Coord b);
bool   isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2);
int    orientation(Coord p, Coord q, Coord r);
bool   doIntersect(Coord p1, Coord q1, Coord p2, Coord q2);
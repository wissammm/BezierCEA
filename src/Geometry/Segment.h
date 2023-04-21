#pragma once
#include "Coord.h"

struct Segment
{
    Coord a;
    Coord b;
};
;
double cross(Coord a, Coord b);
double norm(Coord a);
double abs(Coord a);
Coord  intersect(Coord a1, Coord d1, Coord a2, Coord d2);
Coord  intersect(Segment seg1, Segment seg2);
double dot(Coord a, Coord b);
double proj(Coord a, Coord b);
double angle(Coord a, Coord b);
double distance(Segment seg);
double distance(Coord A, Coord B);
double determinant(Coord a1, Coord a2, Coord b1, Coord b2);
bool   onSegment(Coord p, Coord a, Coord b);
bool   isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2);
int    orientation(Coord p, Coord q, Coord r);
bool   doIntersect(Coord p1, Coord q1, Coord p2, Coord q2);
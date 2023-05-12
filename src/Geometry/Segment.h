#pragma once
#include "Coord.h"
#include <optional>

struct Segment
{
    Coord a;
    Coord b;
};

double               norm(Coord a);
double               abs(Coord a);
Segment              vector(Coord A1, Coord A2, Coord B1, Coord B2);
double               cross(Coord a, Coord b);
double               norm(Coord a);
double               abs(Coord a);
double               dot(Coord a, Coord b);
double               proj(Coord a, Coord b);
double               angle(Coord a, Coord b);
double               distance(Segment seg);
double               distance(Coord A, Coord B);
double               determinant(double a1, double a2, double b1, double b2);
bool                 onSegment(Coord p, Coord a, Coord b);
std::optional<Coord> lineLineIntersection(Coord A, Coord B, Coord C, Coord D);
std::optional<Coord> lineLineIntersection(Segment seg1, Segment seg2);
bool                 isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2);
int                  orientation(Coord p, Coord q, Coord r);
bool                 doIntersect(Coord p1, Coord q1, Coord p2, Coord q2);
double               angle(Coord A, Coord B, Coord C);
double               meanAngleFromControlPoints(std::vector<Coord> controlPoints);
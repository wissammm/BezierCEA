#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"

Coord getIntersectionPoint(Coord a1, Coord a2, Coord b1, Coord b2);
bool isOnSegment(Coord p, Coord a, Coord b);
bool isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2);
int                 orientation(Coord p, Coord q, Coord r);
bool                doIntersect(Coord p1, Coord q1, Coord p2, Coord q2);
bool                touchHull(Curve bez, Segment seg);
std::vector<Coord>  translatePointsTo0(std::vector<Coord> bez);
std::vector<Coord>  rotateToX(std::vector<Coord> bez);
std::vector<double> firstGuesses(Curve bez, Segment seg);
double              getTimeByResult(Coord A, Coord B, Coord C);
double              newtonMethod(Curve bez, double guessT, Segment seg, double epsilone);
std::vector<Coord>  intersectionNewtonMethod(Curve bez, Segment seg, double epsilone);
std::vector<Coord>  intersectionNaive(Curve bez, Segment seg);

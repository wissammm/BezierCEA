#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"

enum OPTIONS{
    NAIVE,
    NEWTON,
};

struct Intersection{
    Coord inter;
    double time;
};

bool touchHull(Curve bez, Segment seg);
double newtonMethod(Curve bez, double guessT, Segment seg, double epsilon);
std::vector<Intersection> intersectionNewtonMethod(Curve bez, Segment seg, double epsilon);
std::vector<Intersection> intersectionNaive(Curve bez, Segment seg, size_t nbPoints);
std::vector<Intersection> getAllIntersections(Segments segments, Curves curves, double epsilone, OPTIONS options);
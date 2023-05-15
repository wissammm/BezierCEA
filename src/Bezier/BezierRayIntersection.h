#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include <optional>

struct BezierRayIntersectionOption
{

    enum { NAIVE, BOUNDING_BOX };
    NewtonOptions      newtonOptions;
    BoundingBoxOptions aabbOptions;
    NaiveOptions       naiveOptions;
};

struct NaiveOptions
{
    bool   useSimpleBoundingBox = true;
    size_t nbPointsOnCurve = 100;
    size_t maxIter = 1e10;
};

struct BoundingBoxOptions
{
    bool   useSimpleBoundingBox = false;
    double flatAngle            = 1e-5;
    size_t maxDepth             = 20;
};

struct BezierWithInitialTime
{
    Bezier bez;
    double tBegin;
    double tEnd;
    size_t depth = 0;
};

double newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, NewtonOptions newtonOption);
bool   isControlPointsFlat(std::vector<Coord> controlPoints, double epsilon);
double newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, BoundingBoxOptions abbOptions);
std::vector<double>    rayBoundingBoxMethod(Bezier bez, Segment ray, BezierRayIntersectionOption aabbOption);
std::vector<CoordTime> intersectionNaiveNewtonMethod(Bezier bez, Segment seg, NaiveOptions naiveOptions);
std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, size_t nbPoints);

// std::vector<CoordTime> getAllCoordTimes(Segments segments, Beziers curves, double epsilone, OPTIONS options);
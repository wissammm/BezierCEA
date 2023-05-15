#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include "Geometry/Newton.h"
#include <optional>

enum { NAIVE = 0, BOUNDING_BOX = 1 };

struct NaiveOptions
{
    bool   useSimpleBoundingBox = true;
    size_t nbPointsOnCurve      = 100;
    size_t maxIter              = 1e10;
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

struct BezierRayIntersectionOption
{
    bool evaluateCoordOnBezier = true;
    NewtonOptions newtonOptions;
    BoundingBoxOptions aabbOptions;
    NaiveOptions       naiveOptions;
};

bool   isControlPointsFlat(std::vector<Coord> controlPoints, double epsilon);
double newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, BoundingBoxOptions aabbOptions);
std::vector<double>    rayBoundingBoxMethod(Bezier bez, Segment ray, BezierRayIntersectionOption aabbOption);
std::vector<CoordTime> intersectionNaiveNewtonMethod(Bezier bez, Segment seg, BezierRayIntersectionOption options);
std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, NaiveOptions naiveOptions);

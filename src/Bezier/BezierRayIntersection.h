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
};

struct BoundingBoxOptions
{
    double epsilonDoublons      = 0.0;
    bool   useSimpleBoundingBox = true;
    double epsilon              = 1e-5;
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
    size_t             mode                  = BOUNDING_BOX;
    bool               evaluateCoordOnBezier = true;
    bool               isSegment             = false;
    double             avoidDouble           = 0.0;
    NewtonOptions      newtonOptions;
    BoundingBoxOptions aabbOptions;
    NaiveOptions       naiveOptions;
};

bool                  isControlPointsFlat(std::vector<Coord> controlPoints, double epsilon);
std::optional<double> newtonMethodIntersectionBezierRay(
    Bezier bez, double guessT, Segment seg, bool timeOnCurve, NewtonOptions options);
std::vector<CoordTime> intersectionBoundingBoxNewton(Bezier bez, Segment seg, BezierRayIntersectionOption options);
std::vector<double>    rayBoundingBoxMethod(Bezier bez, Segment ray, BezierRayIntersectionOption aabbOption);
std::vector<CoordTime> intersectionNaiveNewtonMethod(Bezier bez, Segment seg, BezierRayIntersectionOption options);
std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, NaiveOptions naiveOptions);
std::vector<CoordTime> intersectionRayBezier(Bezier bez, Segment seg, BezierRayIntersectionOption option);

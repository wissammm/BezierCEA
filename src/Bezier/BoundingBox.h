#pragma once
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include <vector>
#include <optional>
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include "Geometry/Segment.h"
#include "Bezier/BoundingBox.h"

struct AABB
{
    Coord  base;
    double w;
    double h;
    AABB();
    AABB(Coord origin, double width, double height) {
        base = origin;
        w    = width;
        h    = height;
    };
};

AABB                  minMaxFromPoints(std::vector<Coord> points);
std::vector<Coord>    AABBtoQuad(AABB aabb);
bool                  isPointInAABB(AABB aabb, Coord point);
bool                  isAABBintersectAABB(AABB aabb1, AABB aabb2);
bool                  isIntersectSegmentBoundingBox(AABB aabb, Segment seg);
std::vector<AABB>     decomposeAABBinTwo(AABB aabb);
std::optional<double> findExtremum(Bezier               derivateFirst,
                                   Bezier               derivateSecond,
                                   double               firstGuess,
                                   char                 axis,
                                   Buffer               first,
                                   Buffer               second,
                                   const NewtonOptions& options = {});
std::vector<Root>     rootsFromLUT(Bezier curve, std::vector<CoordTime> lut);
AABB                  simpleBoundingBox(Bezier curve);
AABB                  convexBoundingBox(Bezier& curve);

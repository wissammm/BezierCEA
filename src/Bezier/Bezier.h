#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include <vector>

using Bezier = std::vector<Coord>;

using Buffer   = std::vector<std::vector<Coord>>;
using Segments = std::vector<Segment>;

struct Curve
{
  public:
    Bezier controlPoint;
    size_t nbControlPoint;
    size_t degree;

    Curve(size_t n) {
        controlPoint   = Bezier(n);
        nbControlPoint = n;
        degree         = nbControlPoint - 1;
    };
    Curve(Bezier bezierControlPoint) {
        controlPoint   = bezierControlPoint;
        nbControlPoint = controlPoint.size();
        degree         = nbControlPoint - 1;
    }
    // Curve();
    Curve() = default;
};
using Curves   = std::vector<Curve>;

struct CurveNormalsAndTangents
{
    std::vector<Coord> curve;
    Segments           normals;
    Segments           tangents;
};
Curve changeOrigin(Curve curve , Coord p);

Buffer                  createBuffer(size_t degree);
Curve                   randomPoint(int n, int y, int x);

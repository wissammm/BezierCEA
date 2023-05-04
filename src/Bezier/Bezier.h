#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include <vector>

using Buffer   = std::vector<std::vector<Coord>>;
using Segments = std::vector<Segment>;

struct CoordTime
{
    Coord  coord;
    double time;
};

struct Root
{
    double time;
    bool isYaxis;
};

struct Bezier
{
  public:
    std::vector<Coord> controlPoint;
    
    size_t             nbControlPoint;
    size_t             degree;

    std::vector<CoordTime> lut;
    std::vector<Root> roots;
    std::vector<Coord> hull;

    Bezier(size_t n) {
        controlPoint   = std::vector<Coord>(n);
        nbControlPoint = n;
        degree         = nbControlPoint - 1;
    };
    Bezier(std::vector<Coord> bezierControlPoint) {
        controlPoint   = bezierControlPoint;
        nbControlPoint = controlPoint.size();
        degree         = nbControlPoint - 1;
    }

    // Curve();
    Bezier() = default;

    
};
using Beziers = std::vector<Bezier>;

struct BezierNormalsAndTangents
{
    std::vector<Coord> curve;
    Segments           normals;
    Segments           tangents;
};
Bezier changeOrigin(Bezier curve, Coord p);

Buffer createBuffer(size_t degree);
Coord randomPoint(int x, int y);
std::vector<Coord> randomPoints(int n, int x, int y);
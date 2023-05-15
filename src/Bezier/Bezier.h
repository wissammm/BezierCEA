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
    bool   isYaxis;
};

struct Bezier
{
  public:
    std::vector<Coord> controlPoint;

    Bezier(size_t n) { controlPoint = std::vector<Coord>(n); };
    Bezier(std::vector<Coord> bezierControlPoint) { controlPoint = bezierControlPoint; }

     size_t nbControlPoint() const { return controlPoint.size(); };
     size_t degree() const { return controlPoint.size() - 1; };
    // Curve();
    Bezier() = default;

  private:
};
using Beziers = std::vector<Bezier>;

struct BezierNormalsAndTangents
{
    std::vector<Coord> curve;
    Segments           normals;
    Segments           tangents;
};

Bezier changeOrigin(Bezier curve, Coord p);
Bezier changeOriginTo0(Bezier curve, Coord p);
Bezier rotatePoints(Bezier curve);

Buffer             createBuffer(size_t degree);
Coord              randomPoint(int x, int y);
std::vector<Coord> randomPoints(int n, int x, int y);
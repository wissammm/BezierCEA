#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include <vector>
#include <Eigen/Dense>

using Bezier = std::vector<Coord>;
using Eigen::MatrixXd;
using Buffer   = std::vector<std::vector<Coord>>;
using Segments = std::vector<Segment>;

struct Curve
{
  public:
    Bezier controlPoint;
    size_t nbControlPoint;
    size_t degree;
    
    Curve( size_t n) {
        controlPoint   = Bezier(nbControlPoint);
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

struct CurveNormalsAndTangents
{
    std::vector<Coord> curve;
    Segments           normals;
    Segments           tangents;
};

Curve                   elevate(const Curve& curve);
Curve                   derivate(const Curve& curve);
Curve                   lower(const Curve& curve);
Coord                   computeTangent(Coord deriv_time_t);
Coord                   computeNormal(Coord tengent);
Coord                   evalCasteljau(const Bezier& bezier, double t, Buffer& buffer);
Buffer                  createBuffer(size_t degree);
std::vector<Coord>      casteljau(const Curve& Curve, size_t nb_points_on_curve);
CurveNormalsAndTangents normalsAndTangents(const Curve& Curve, size_t nb_points_on_curve, double factor);
std::array<Curve, 2>    decompose(const Curve& curve, double t);
Curve                   randomPoint(int n, int y, int x);

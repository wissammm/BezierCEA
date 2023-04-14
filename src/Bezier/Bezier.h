#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include <vector>
#include <Eigen/Dense>

using Bezier = std::vector<Coord>;
using Eigen::MatrixXd;
using Buffer   = std::vector<std::vector<Coord>>;
using Segments = std::vector<Segment>;

struct CurveNormalsAndTangents
{
    std::vector<Coord> curve;
    Segments           normals;
    Segments           tangents;
};


Bezier                  elevate(const Bezier& curve);
Bezier                  derivate(const Bezier& curve);
Bezier                  lower(const Bezier& curve);
Coord                   computeTangent(Coord deriv_time_t);
Coord                   computeNormal(Coord tengent);
Coord                   evalBezier(const Bezier& bezier, double t);
std::vector<Coord>      bezier(const std::vector<Coord>& tab, size_t nb_points_on_curve);
Coord                   evalCasteljau(const Bezier& bezier, double t, Buffer& buffer);
Buffer                  createBuffer(size_t degree);
std::vector<Coord>      casteljau(const Bezier& bezier, size_t nb_points_on_curve);
CurveNormalsAndTangents normalsAndTangents(const Bezier& bezier, size_t nb_points_on_curve, double factor);
std::array<Bezier, 2>   decompose(const Bezier& curve, double t);
Bezier                  randomPoint(int n, int y, int x);

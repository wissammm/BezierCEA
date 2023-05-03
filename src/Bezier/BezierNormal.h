#pragma once
#include "Geometry/Coord.h"
#include "Bezier.h"

Coord                   computeNormal(Coord tengent);
Coord                   computeTangent(Coord deriv_time_t);
BezierNormalsAndTangents normalsAndTangents(const Bezier& bezier, size_t nb_points_on_curve, double factor);
Coord                   normal(Bezier curve, size_t time);
Coord                   tangente(Bezier curve, size_t time);
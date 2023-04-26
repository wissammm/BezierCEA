#pragma once
#include "Geometry/Coord.h"
#include "Bezier.h"

Coord                   computeNormal(Coord tengent);
Coord                   computeTangent(Coord deriv_time_t);
CurveNormalsAndTangents normalsAndTangents(const Curve& bezier, size_t nb_points_on_curve, double factor);
Coord                   normal(Curve curve, size_t time);
Coord                   tangente(Curve curve, size_t time);
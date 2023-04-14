#pragma once

#include "Bezier.h"
#include "BezierEvaluate.h"
#include "Geometry/Coord.h"
#include "Geometry/Segment.h"

CurveNormalsAndTangents normalsAndTangents(const Curve& bezier, size_t nb_points_on_curve, double factor);
Coord                   normal(Curve curve, size_t time);
Coord                   tangente(Curve curve, size_t time);
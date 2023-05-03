#pragma once

#include "Geometry/Coord.h"
#include "Bezier.h"

Coord               evalCasteljau(const Bezier& curve, double t, Buffer& buffer);
std ::vector<Coord> casteljau(const Bezier& curve, size_t nb_points_on_curve);
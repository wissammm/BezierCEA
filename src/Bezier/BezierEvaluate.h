#pragma once

#include "Geometry/Coord.h"
#include "Bezier.h"

std::vector<CoordTime> computeLUT(Bezier bez, size_t nbPointsLUT);
Coord                  evalCasteljau(const Bezier& curve, double t, Buffer& buffer);
std ::vector<Coord>    casteljau(const Bezier& curve, size_t nb_points_on_curve);
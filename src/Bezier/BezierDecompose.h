#pragma once

#include "Geometry/Coord.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include <array>


std::array<Curve, 2> decompose(const Curve& curve, double t);
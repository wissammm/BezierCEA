#pragma once

#include "Geometry/Coord.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include <array>


std::array<Bezier, 2> decompose(const Bezier& curve, double t);
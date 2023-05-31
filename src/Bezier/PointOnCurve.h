#pragma once

#include "Geometry/Coord.h"
#include "Bezier/Bezier.h"

CoordTime getNearestPointOnCurve(Bezier bez, Coord p, size_t nbIter);
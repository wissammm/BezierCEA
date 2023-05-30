#pragma once
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"

CoordTime getNearestPointOnCurve(Bezier bez, Coord p, size_t nbIter);
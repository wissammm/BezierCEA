#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"

bool segmentIntersection(Coord &intersect, Segment s1, Segment s2, Curve bezier);
// bool rayIntersection(Coord &intersect, Coord p, Coord vec, Curve bezier);


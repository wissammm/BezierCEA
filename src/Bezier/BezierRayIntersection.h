#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include <optional>


double                 newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, double epsilon);
std::vector<CoordTime> intersectionNewtonMethod(Bezier  bez,
                                                Segment seg,
                                                double  epsilon         = 1e-9,
                                                size_t  nbPointOnBezier = 100);
std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, size_t nbPoints);
// std::vector<CoordTime> getAllCoordTimes(Segments segments, Beziers curves, double epsilone, OPTIONS options);
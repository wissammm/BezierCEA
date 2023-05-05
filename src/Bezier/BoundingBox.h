#pragma once
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include <vector>
#include <optional>
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include "Geometry/Segment.h"


std::vector<Coord> minMaxFromPoints(std::vector<Coord> points);

std::optional<double> findExtremum(Bezier derivateFirst,
                                   Bezier derivateSecond,
                                   double firstGuess,
                                   char   axis,
                                   Buffer first,
                                   Buffer second,
                                   const NewtonOptions& options = {});
std::vector<Root>     rootsFromLUT(Bezier curve, std::vector<CoordTime> lut);
std::vector<Coord>    simpleBoundingBox(Bezier curve);
std::vector<Coord>    convexBoundingBox(Bezier& curve);

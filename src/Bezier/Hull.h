#pragma once
#include "Geometry/Coord.h"
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
                                   double epsilon      = 1e-5,
                                   double minRange     = -1,
                                   double maxRange     = 2,
                                   double learningRate = 1.);
std::vector<Root>     rootsFromLUT(Bezier curve, std::vector<CoordTime> lut);
std::vector<Coord>    simpleHull(Bezier curve);
std::vector<Coord>    convexHull(Bezier& curve);
